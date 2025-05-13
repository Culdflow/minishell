/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:55:52 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/29 01:34:19 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	char	**result;
	t_token	last_token;

	result = malloc(sizeof(char *) * (get_split_size(tokens) + 1));
	last_token = INVALID;
	i = -1;

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
	int		nb_of_splits;
	int		my_i;
	t_token	last_token;

	nb_of_splits = 0;
	my_i = 0;
	while (tokens[my_i] == INVALID)
		my_i++;
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
	int		is_differentquote;
	int		y;
	t_token	last_token;

	i = 0;
	y = 0;
	last_token = -2;
	is_differentquote = FALSE;
	while (split[i])
		i++;
	result = malloc(sizeof(t_token) * (i + 1));
	i = 0;
	while (tokens[y])
	{
		if (tokens[y] != last_token && tokens[y] != INVALID)
			is_differentquote = TRUE;
		if (is_differentquote == TRUE)
		{
			result[i] = tokens[y];
			i++;
			is_differentquote = FALSE;
		}
		last_token = tokens[y];
		y++;
	}
	result[i] = 0;
	free(tokens);
	return (result);
}
