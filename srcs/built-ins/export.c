/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:59:29 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/26 02:00:11 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while(tab && tab[i])
		i++;
	return (i);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	export(char ***env, char *str)
{
	char	**result;
	int		tab_size;
	int		i;

	i = 0;
	tab_size = tablen(env) + 2;
	result = malloc(tab_size * sizeof(char *));
	while (env && env[i])
	{
		result[i] = ft_strdup((*env)[i]);
		i++;
	}
	result[i++] = ft_strdup(str);
	result[i] = 0;
	free_tab(*env);
	*env = result;
}