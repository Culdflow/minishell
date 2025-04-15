/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:59:29 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/15 03:32:44 by dfeve            ###   ########.fr       */
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
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	env_arg_len(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	return (i);
}

void	ft_export(char ***env, char *str)
{
	char	**result;
	int		tab_size;
	int		is_found;
	int		i;

	i = 0;
	is_found = FALSE;
	tab_size = tablen(*env) + 2;
	result = malloc(tab_size * sizeof(char *));
	while (env && *env && (*env)[i])
	{
		if (ft_strncmp((*env)[i], str, env_arg_len((*env)[i])) == 0)
		{
			result[i] = str;
			is_found = TRUE;
		}
		else
			result[i] = ft_strdup((*env)[i]);
		i++;
	}
	if (is_found == FALSE)
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
		if (ft_strncmp((*env)[i], str, env_arg_len((*env)[i])))
			result[y++] = *env[i];
		i++;
	}
	result[y] = 0;
	free_tab(*env);
	*env = result;
}

char	**copy_env(char **env)
{
	char	**result;
	int		i;

	result = malloc(sizeof(char *) * (tablen(env) + 1));
	i = 0;
	while (env && env[i])
	{
		result[i] = ft_strdup(env[i]);
		i++;
	}
	result[i] = 0;
	return (result);
}