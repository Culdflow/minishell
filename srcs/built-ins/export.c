/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:59:29 by dfeve             #+#    #+#             */
/*   Updated: 2025/03/06 15:32:18 by dfeve            ###   ########.fr       */
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

void	ft_export(char ***env, char *str)
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

void	ft_unset(char ***env, char *str)
{
	int		i;
	int		y;
	char	**result;

	i = 0;
	y = 0;
	result = malloc(tablen(*env) * sizeof (char *));
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], str, ft_strlen(str)) != 0)
			result[y++] = *env[i];
		i++;
	}
	result[y] = 0;
	free_tab(*env);
	*env = result;
}