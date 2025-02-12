/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 01:13:21 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/12 18:07:55 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_in_env(char **env, char *str)
{
	int	i;
	int	size;

	i = 0;
	while (env && env[i])
	{
		size = 0;
		while (env[i][size])
		{
			if (env[i][size++] == '=')
				break ;
		}
		if (ft_strncmp(str, env[i], size - 1) == 0)
			return (env[i] + size);
		i++;
	}
	return (NULL);
}

void	add_in_str(char **src, char *add, int add_in)
{
	int		i;
	int		j;
	int		size;
	char	*result;

	size = ft_strlen(*src) + ft_strlen(add) + 1;
	if (add_in > (int)ft_strlen(*src))
		return ;
	result = malloc(size);
	i = 0;
	while ((*src)[i] && i < add_in)
		result[i] = (*src)[i++];
	j = 0;
	while (add[j])
		result[i + j] = add[j++];
	while ((*src)[i])
		result[i + j] = (*src)[i++];
	result[i + j] = 0;
	*src = result;
}
