/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:22:17 by dfeve             #+#    #+#             */
/*   Updated: 2025/05/13 17:31:38 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	switch_tab_el(char ***tab, int from, int to)
{
	char	**new_tab;
	char	*sfrom;
	char	*tmp;
	int		i;
	int		y;
	
	i = 0;
	y = 0;
	tmp = NULL;
	new_tab = malloc((tablen((*tab)) + 1) * sizeof(char *));
	while ((*tab) && (*tab)[i])
	{
		if (i == from)
			sfrom = (*tab)[i];
		i++;
	}
	i = 0;
	while ((*tab) && (*tab)[i])
	{
		if (i != from)
		{
			if (i == to)
			{
				new_tab[y++] = sfrom;
				new_tab[y++] = (*tab)[i];
			}
			else
				new_tab[y++] = (*tab)[i];
		}
		i++;
	}
	new_tab[y] = 0;
	free(*tab);
	*tab = new_tab;
}

void	rm_rd(t_tokenized *tokenized, int i)
{
	int		y;
	char	*new_val;

	y = 0;
	new_val = NULL;
	free(tokenized->split_input[i]);
	tokenized->split_input[i] = ft_strdup("\a\0");
	if (tokenized->split_input[i + 1])
	{
		new_val = ft_strdup("\a\0");
		while (tokenized->split_input[i + 1][y])
		{
			if (tokenized->split_input[i + 1][y] == ' ')
			{
				free(new_val);
				new_val = ft_strdup(tokenized->split_input[i + 1] + (y + 1));
				break ;
			}
			y++;
		}
		free(tokenized->split_input[i + 1]);
		tokenized->split_input[i + 1] = new_val;
	}
}

int	get_element_after_space(char **tab, int i)
{
	while (tab && tab[++i])
	{
		if (is_only_spaces(tab[i]) == FALSE)
			return (i);
	}
	return (i);
}

void	add_el_to_str(char **str, char *el)
{
	char *result;

	result = ft_strjoin(*str, el);
	free(*str);
	*str = result;
}

int	parget_infile(t_tokenized *tokenized)
{
	int		i;
	int		el_i;
	char	*infile;
	char	**split;
	char	*heredoc_modif;
	int		fd;
	
	i = 0;
	el_i = 0;
	heredoc_modif = NULL;
	infile = NULL;
	fd = 0;
	split = NULL;
	tokenized->is_heredoc = FALSE;
	while (tokenized->split_input && tokenized->split_input[i])
	{
		if (tokenized->tokens[i] == R_DIR_IN)
		{
			el_i = get_element_after_space(tokenized->split_input, i);
			if (!tokenized->split_input[el_i] || tokenized->tokens[el_i] != WORD)
			{
				ft_parerror("syntax error near unexpected token\n", tokenized);
				return (fd);
			}
			split = ft_split(tokenized->split_input[i + 1], ' ');
			if (access(split[0], F_OK) == -1 || access(split[0], R_OK) == -1 )
			{
				ft_parerror("No such file or directory\n", tokenized);
				return (fd);
			}
			if (infile)
				free(infile);
			infile = ft_strdup(split[0]);
			free_tab(split);
			rm_rd(tokenized, i);
		}
		if (tokenized->tokens[i] == RR_DIR_IN)
		{
			el_i = get_element_after_space(tokenized->split_input, i);
			if (!tokenized->split_input[el_i] || tokenized->tokens[el_i] != WORD)
			{
				ft_parerror("syntax error near unexpected token\n", tokenized);
				return (fd);
			}
			tokenized->is_heredoc = TRUE;
			free(tokenized->split_input[i]);
			tokenized->split_input[i] = ft_strdup("\a\0");
			add_el_to_str(&tokenized->split_input[el_i], "|");
			switch_tab_el(&tokenized->split_input, el_i, 0);
			return (-10);
		}
		i++;
	}
	if (infile)
	{
		fd = open(infile, O_RDONLY, 0644);
		free(infile);
	}
	return (fd);
}

void	fill_outfiles(t_outfile *start)
{
	int fd;

	fd = 0;
	if (!start)
		return ;
	while (start->next)
	{
		if (!start->is_append)
		{
			fd = open(start->file, O_TRUNC | O_CREAT, 0644);
			write(fd, "", 1);
			close(fd);
		}
		start = start->next;
	}
}

int	parget_outfile(t_tokenized *tokenized)
{
	int			i;
	int			el_i;
	t_outfile	*outfiles;
	char		**split;
	int			fd;
	
	i = 0;
	el_i = 0;
	fd = 1;
	split = NULL;
	outfiles = NULL;
	while (tokenized->split_input && tokenized->split_input[i])
	{
		if (tokenized->tokens[i] == R_DIR_OUT || tokenized->tokens[i] == RR_DIR_OUT)
		{
			el_i = get_element_after_space(tokenized->split_input, i);
			if (!tokenized->split_input[el_i] || tokenized->tokens[el_i] != WORD)
			{
				ft_parerror("syntax error near unexpected token\n", tokenized);
				return (fd);
			}
			split = ft_split(tokenized->split_input[el_i], ' ');
			rm_rd(tokenized, i);
			outfiles = add_outfile(outfiles, split[0], tokenized->tokens[i] == RR_DIR_OUT, tokenized);
			free_tab(split);
		}
		i++;
	}
	fill_outfiles(outfiles);
	if (outfiles)
	{
		if (get_last_outfile(outfiles)->is_append)
			fd = open(get_last_outfile(outfiles)->file, O_APPEND | O_WRONLY | O_CREAT, 0644);
		else
		{
			fd = open(get_last_outfile(outfiles)->file, O_TRUNC | O_CREAT, 0644);
			close(fd);
			fd = open(get_last_outfile(outfiles)->file, O_WRONLY, 0644);
		}
	}
	free_outfiles(outfiles);
	return (fd);
}

