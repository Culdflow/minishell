/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:55:52 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/05 17:08:59 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*create_str_for_split(char *str, t_token *tokens)
{
	int		i;
	int		y;
	int		size;
	char	*result;

	i = 0;
	y = -1;
	size = strlen_tokens(tokens, &i);
	result = malloc(size + 1);
	size = 0;
	while (++y < i)
		if (tokens[y] != INVALID)
			result[size++] = str[y];
	result[size] = 0;
	return (result);
}

char	**tokenizer_split(char *str, t_token *tokens)
{
	int		i;
	int		index;
	int		start;
	char	**result;
	t_token	last_token;

	result = malloc(sizeof(char *) * (get_split_size(tokens) + 1));
	last_token = INVALID;
	i = -1;
	start = 0;
	index = 0;
	while (tokens[++i])
	{
		if (tokens[i] != INVALID)
		{
			if (tokens[i] != last_token)
				result[index++] = create_str_for_split(str + i, tokens + i);
			last_token = tokens[i];
		}
	}
	result[index] = 0;
	return (result);
}

int	get_split_index(t_token *tokens, int i)
{
	int	nb_of_splits;
	int	my_i;
	t_token	last_token;

	nb_of_splits = 0;
	my_i = 0;
	last_token = tokens[my_i];
	while (tokens[my_i])
	{
		if (tokens[my_i] != INVALID)
		{
			if (tokens[my_i] != last_token)
				nb_of_splits++;
			last_token = tokens[my_i];
		}
		if (nb_of_splits >= i)
			break ;
		my_i++;
	}
	return (my_i);
}

t_token	*get_tokens(char **split, t_token *tokens)
{
	t_token	*result;
	int		i;

	i = 0;
	while (split[i])
		i++;
	result = malloc(sizeof(t_token) * (i + 1));
	i = 0;
	while (split[i])
	{
		result[i] = tokens[get_split_index(tokens, i)];
		i++;
	}
	result[i] = 0;
	free(tokens);
	return (result);
}