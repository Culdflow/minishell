/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:22:17 by dfeve             #+#    #+#             */
/*   Updated: 2025/03/26 18:43:10 by dfeve            ###   ########.fr       */
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
			if (!tokenized->split_input[i + 1])
			//syntax error
			if (access(tokenized->split_input[i + 1], F_OK | R_OK) == -1)
			//file doesnt exist or permission error
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
	while (start->next)
	{
		fd = open(start->file, O_WRONLY);
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
		if (tokenized->tokens[i] == R_DIR_IN)
		{
			if (!tokenized->split_input[i + 1])
			//syntax error
			add_outfile(outfiles, tokenized->split_input[i + 1]);
		}
		i++;
	}
	fill_outfiles(outfiles);
	if (outfiles)
		fd = open(get_last_outfile(outfiles), O_RDONLY);
	free(outfiles);
	return (fd);
}
