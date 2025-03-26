/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:11:23 by dfeve             #+#    #+#             */
/*   Updated: 2025/03/26 18:41:34 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_outfile	*new_outfile(char *fileName)
{
	t_outfile	*result;
	
	if (access(fileName, F_OK | W_OK ) == -1)
	{
		//error management
		return (0);
	}
	result = malloc(sizeof(t_outfile));
	result->file = fileName;
	result->next = NULL;
	return (result);
}

t_outfile	*add_outfile(t_outfile *start, char *fileName)
{
	if (!start)
		start =  new_outfile(fileName);
	else
		start->next = new_outfile(fileName);
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
		free(outfiles);
		outfiles = tmp;
	}
}