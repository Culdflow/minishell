/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:15:38 by greg              #+#    #+#             */
/*   Updated: 2025/02/14 17:39:39 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_builtins(char *str)
{
    if (!ft_strncmp(str, "pwd", 3) || !ft_strncmp(str, "exit", 4) || !ft_strncmp(str, "env", 3)
    || !ft_strncmp(str, "cd", 2) || !ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "export", 6)
    || !ft_strncmp(str, "unset", 5))
		return (1);
    return (0);
}

char *sanitize_str(char *str)
{
    char *trimmed;
	
	if (!str)
		return (NULL);
	trimmed = ft_strtrim(str, " ");
    free(str);
    return trimmed;
}

char *get_chevron_indices(char *pipe, int index[2])
{
    char *chevron;

    chevron = ft_strchr(pipe, '<');
    if (chevron)
        index[0] = chevron - pipe;
    else
        index[0] = 0;
    chevron = ft_strchr(pipe, '>');
    if (chevron)
        index[1] = chevron - pipe;
    else
        index[1] = ft_strlen(pipe);
    return (chevron);
}
