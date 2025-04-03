/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:22:17 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/03 23:54:38 by dfeve            ###   ########.fr       */
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

int	parget_infile(t_tokenized *tokenized)
{
	int		i;
	char	*infile;
	char	**split;
	int		fd;
	
	i = 0;
	infile = NULL;
	fd = 0;
	split = NULL;
	while (tokenized->split_input[i])
	{
		if (tokenized->tokens[i] == R_DIR_IN)
		{
			if (!tokenized->split_input[i + 1])
				return (fd);
			//syntax error
			split = ft_split(tokenized->split_input[i + 1], ' ');
			if (access(split[0], F_OK) == -1 || access(split[0], R_OK) == -1 )
				return (fd);
			//file doesnt exist or permission error;
			printf("infile name %s\n", split[0]);
			if (infile)
				free(infile);
			infile = ft_strdup(split[0]);
			free_tab(split);
			rm_rd(tokenized, i);
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
		fd = open(start->file, O_TRUNC);
		write(fd, "", 1);
		close(fd);
		start = start->next;
	}
}

int	parget_outfile(t_tokenized *tokenized)
{
	int			i;
	t_outfile	*outfiles;
	char		**split;
	int			fd;
	
	i = 0;
	fd = 1;
	split = NULL;
	outfiles = NULL;
	while (tokenized->split_input[i])
	{
		if (tokenized->tokens[i] == R_DIR_OUT || tokenized->tokens[i] == RR_DIR_OUT)
		{
			if (!tokenized->split_input[i + 1])
				return (fd);
			//syntax error
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
			fd = open(get_last_outfile(outfiles)->file, O_APPEND | O_WRONLY);
			printf("is append opened in append\n");
		}
		else
		{
			fd = open(get_last_outfile(outfiles)->file, O_TRUNC);
			write(fd, "", 1);
			close(fd);
			fd = open(get_last_outfile(outfiles)->file, O_WRONLY);
		}
	}
	free_outfiles(outfiles);
	return (fd);
}
