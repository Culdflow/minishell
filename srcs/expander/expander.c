/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 01:13:21 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/26 22:26:14 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	remove_char_str(char **str, char rm_char)
{
	int		i;
	int		y;
	int		size;
	char	*result;

	i = 0;
	size = 0;
	if (!str && !(*str))
		return ;
	while ((*str)[i])
		if ((*str)[i++] == rm_char)
			size++;
	result = malloc((ft_strlen(*str) - size) + 1);
	i = 0;
	y = 0;
	while ((*str)[i])
	{
		if ((*str)[i] != rm_char)
			result[y++] = (*str)[i];
		i++;
	}
	result[y] = 0;
	free(*str);
	*str = result;
}

int	check_if_dollar(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_in_env(char **env, char **str)
{
	int	i;
	int	y;
	int	size;

	i = 0;
	y = -1;
	while (env && env[i])
	{
		size = -1;
		while (env[i][++size])
		{
			if (env[i][size] == '=')
				break ;
		}
		if (ft_strncmp(*str, env[i], size) == 0)
		{
			while ((*str)[++y] && y <= (size - 1))
				(*str)[y] = '\a';
			return (env[i] + size + 1);
		}
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
	if (add_in > (int)ft_strlen(*src) - 1 || add_in < 0)
		return ;
	result = malloc(size);
	i = -1;
	while ((*src)[++i] && i < add_in)
		result[i] = (*src)[i];
	j = -1;
	while (add[++j])
		result[i + j] = add[j];
	i -= 1;
	while ((*src)[++i])
		result[i + j] = (*src)[i];
	result[i + j] = 0;
	free(*src);
	*src = result;
}

void	replace_while_word(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) == 1)
	{
		str[i] = '\a';
		return ;
	}
	while (str[i] != ' ' && str[i] != '$')
		str[i++] = '\a';
}

void	expand(t_tokenized *tokenized, char **env)
{
	int		i;
	int		y;
	char	*split_input_str;
	char	*env_value;

	i = 0;
	y = 0;
	while (tokenized->split_input[i])
	{
		y = 0;
		while (check_if_dollar(tokenized->split_input[i]) != -1)
		{
			y += check_if_dollar(tokenized->split_input[i] + y);
			tokenized->split_input[i][y] = '\a';
			y++;
			split_input_str = tokenized->split_input[i] + y;
			env_value = get_in_env(env, &split_input_str);
			if (env_value)
				add_in_str(&tokenized->split_input[i], env_value, y);
			else
				replace_while_word(split_input_str);
		}
		remove_char_str(&tokenized->split_input[i], '\a');
		i++;
	}
}


/////////////////////////////////////////////////////
/////////-------------TODO------------------/////////
/////////////////////////////////////////////////////
//---EXPAND ERROR WHEN WORD IS NOT ENTIRELY = TO ENV/
//-------------------------------------------------//
//-------------------------------------------------//
//-------------------------------------------------//
//-------------------------------------------------//
//-------------------------------------------------//
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
