/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:11:23 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/19 19:28:28 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_outfile	*new_outfile(char *fileName, int is_append, t_tokenized *tokenized)
{
	t_outfile	*result;
	
	if (access(fileName, F_OK | W_OK ) == -1)
	{
		if (errno == EACCES || errno == EISDIR)
		{
			ft_parerror(fileName, tokenized);
			return (NULL);
		}
	}
	result = malloc(sizeof(t_outfile));
	result->file = ft_strdup(fileName);
	result->is_append = is_append;
	result->next = NULL;
	return (result);
}

t_outfile	*add_outfile(t_outfile *start, char *fileName, int is_append, t_tokenized *tokenized)
{
	t_outfile *tmp;

	tmp = get_last_outfile(start);
	if (!start)
		start =  new_outfile(fileName, is_append, tokenized);
	else
		tmp->next = new_outfile(fileName, is_append, tokenized);
	return (start);
}

t_outfile	*get_last_outfile(t_outfile *start)
{
	if (!start)
		return (NULL);
	while (start->next)
		start = start->next;
	return (start);
}

void	free_outfiles(t_outfile *outfiles)
{
	t_outfile *tmp;

	while (outfiles)
	{
		tmp = outfiles->next;
		free(outfiles->file);
		free(outfiles);
		outfiles = tmp;
	}
}