/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:22:17 by dfeve             #+#    #+#             */
/*   Updated: 2025/03/31 17:49:24 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	rm_rd(t_tokenized *tokenized, int i)
{
	free(tokenized->split_input[i]);
	tokenized->split_input[i] = ft_strdup("\a");
	free(tokenized->split_input[i + 1]);
	tokenized->split_input[i + 1] = ft_strdup("\a");
}

int	parget_infile(t_tokenized *tokenized)
{
	int		i;
	char	*infile;
	int		fd;
	
	i = 0;
	infile = NULL;
	fd = 0;
	while (tokenized->split_input[i])
	{
		if (tokenized->tokens[i] == R_DIR_IN)
		{
			if (!tokenized->split_input[i + 1])
				return (fd);
			//syntax error
			printf("isn't syntax error\n");
			if (access(tokenized->split_input[i + 1], F_OK) == -1 || access(tokenized->split_input[i + 1], R_OK) == -1 )
				return (fd);
			//file doesnt exist or permission error;
			printf("infile name %s\n", tokenized->split_input[i + 1]);
			if (infile)
				free(infile);
			infile = ft_strdup(tokenized->split_input[i + 1]);
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
	int			fd;
	
	i = 0;
	fd = 1;
	outfiles = NULL;
	while (tokenized->split_input[i])
	{
		if (tokenized->tokens[i] == R_DIR_OUT)
		{
			if (!tokenized->split_input[i + 1])
				return (fd);
			//syntax error
			printf("found outfile = %s\n", tokenized->split_input[i + 1]);
			outfiles = add_outfile(outfiles, tokenized->split_input[i + 1]);
			rm_rd(tokenized, i);
			printf("outfiles->name = %s\n", outfiles->file);
		}
		i++;
	}
	fill_outfiles(outfiles);
	if (outfiles)
	{
		fd = open(get_last_outfile(outfiles)->file, O_TRUNC);
		write(fd, "", 1);
		close(fd);
		fd = open(get_last_outfile(outfiles)->file, O_WRONLY);
	}
	free_outfiles(outfiles);
	return (fd);
}
