/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:22:17 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/15 03:55:02 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	while (tab && tab[i])
	{
		if (tab[i][0] != ' ')
			return (i);
		i++;
	}
	return (i);
}

int	parget_infile(t_tokenized *tokenized)
{
	int		i;
	int		el_i;
	char	*infile;
	char	**split;
	int		fd;
	
	i = 0;
	el_i = 0;
	infile = NULL;
	fd = 0;
	split = NULL;
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
			printf("infile name %s\n", split[0]);
			if (infile)
				free(infile);
			infile = ft_strdup(split[0]);
			free_tab(split);
			rm_rd(tokenized, i);
		}
		if (tokenized->tokens[i] == RR_DIR_IN)
		{
			if (!tokenized->split_input[i + 1] || tokenized->tokens[i + 1] != WORD)
			{
				ft_parerror("syntax error near unexpected token `newline'\n", tokenized);
				return (fd);
			}
			free(tokenized->split_input[i]);
			tokenized->split_input[i] = ft_strdup("\a\0");
			return (-10);
		}
		i++;
	}
	if (infile)
	{
		fd = open(infile, O_RDONLY);
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
			fd = open(start->file, O_TRUNC | O_CREAT);
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
			printf("tokenized->tokens[i + 1] = %s%d\n",tokenized->split_input[i + 1], tokenized->tokens[i + 1]);
			if (!tokenized->split_input[el_i] || tokenized->tokens[el_i] != WORD)
			{
				ft_parerror("syntax error near unexpected token\n", tokenized);
				return (fd);
			}
			split = ft_split(tokenized->split_input[i + 1], ' ');
			outfiles = add_outfile(outfiles, split[0], tokenized->tokens[i] == RR_DIR_OUT);
			free_tab(split);
			rm_rd(tokenized, i);
			printf("outfiles->name = %s\nis_append = %d\n", get_last_outfile(outfiles)->file, get_last_outfile(outfiles)->is_append);
		}
		i++;
	}
	fill_outfiles(outfiles);
	if (outfiles)
	{
		if (get_last_outfile(outfiles)->is_append)
		{
			fd = open(get_last_outfile(outfiles)->file, O_APPEND | O_WRONLY | O_CREAT, 0644);
			printf("is append opened in append\n");
		}
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
