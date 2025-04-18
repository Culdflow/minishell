/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:58:31 by dfeve             #+#    #+#             */
/*   Updated: 2025/03/06 16:02:49 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	strlen_tokens(t_token *tokens, int	*i)
{
	int		size;
	t_token	last_token;

	size = 0;
	last_token = tokens[*i];
	while (tokens[*i])
	{
		if (tokens[*i] != INVALID)
		{
			if (tokens[*i] != last_token)
				break ;
			size++;
			last_token = tokens[*i];
		}
		(*i)++;
	}
	return (size);
}

int	get_split_size(t_token *tokens)
{
	int		i;
	int		result;
	t_token	last_token;

	i = 0;
	result = 0;
	last_token = INVALID;
	while (tokens[i])
	{
		if (tokens[i] != INVALID)
		{
			if (tokens[i] != last_token)
				result++;
			last_token = tokens[i];
		}
		i++;
	}
	return (result);
}

t_token	get_token(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '&')
		return (AND);
	if (c == '<')
		return (R_DIR_IN);
	if (c == '>')
		return (R_DIR_OUT);
	if (c == '\'')
		return (QUOTE);
	if (c == '\"')
		return (D_QUOTE);
	// if (!is_space(c))
	// 	return (WORD);
	else
		return (WORD);
}

void	tokenize_quotes(t_token **tokens)
{
	int		i;
	t_token quote;

	i = 0;
	while ((*tokens)[i])
	{
		if ((*tokens)[i] == QUOTE || (*tokens)[i] == D_QUOTE)
		{
			quote = (*tokens)[i];
			(*tokens)[i++] = INVALID;
			while ((*tokens)[i] != quote)
				(*tokens)[i++] = quote;
			(*tokens)[i] = INVALID;
		}
		i++;
	}
}

t_token	*tokenize(char *str)
{
	t_token	*result;
	int		i;

	result = malloc(sizeof(t_token) * (ft_strlen(str) + 1));
	i = -1;
	while (str[++i])
		result[i] = get_token(str[i]);
	result[i] = 0;
	tokenize_quotes(&result);
	return (result);
}
