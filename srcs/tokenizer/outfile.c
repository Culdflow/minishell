/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:22:17 by dfeve             #+#    #+#             */
/*   Updated: 2025/03/26 19:44:34 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			printf("found rdir in\n");
			if (!tokenized->split_input[i + 1])
				return (fd);
			//syntax error
			printf("isn't syntax error\n");
			// if (access(tokenized->split_input[i + 1], F_OK) == -1 || access(tokenized->split_input[i + 1], R_OK) == -1 )
			// 	return (fd);
			//file doesnt exist or permission error
			printf("infile name =%s\n", tokenized->split_input[i + 1]);
			infile = tokenized->split_input[i + 1];
		}
		i++;
	}
	if (infile)
		fd = open(infile, O_RDONLY);
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
