/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:58:31 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/05 15:28:31 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if (c == '$')
		return(VAR);
	if (c == '<')
		return (R_DIR_IN);
	if (c == '>')
		return (R_DIR_OUT);
	if (c == '\'')
		return (QUOTE);
	if (c == '\"')
		return (D_QUOTE);
	if (!is_space(c))
		return (WORD);
	else
		return (INVALID);
}

void	token_quote_replace(t_token **tokens, t_token quote, int *i, int first_quote, int last_quote)
{
	*i = first_quote + 1;
	while (*i < last_quote)
	{
		if ((*tokens)[*i] != quote)
			(*tokens)[*i] = WORD;
		else
			(*tokens)[*i] = INVALID;
		(*i)++;
	}
	*i = last_quote + 1;
}

void	tokenize_quotes(t_token **tokens, int *i)
{
	int		first_quote;
	int		nb_of_quotes;
	int		last_quote;
	t_token	quote;

	quote = (*tokens)[*i];
	first_quote = *i;
	last_quote = *i;
	nb_of_quotes = 0;
	while ((*tokens)[*i])
	{
		if ((*tokens)[*i] == quote)
		{
			nb_of_quotes++;
			last_quote =  *i;
		}
		if ((*tokens)[*i] != INVALID && (*tokens)[*i] != QUOTE && (*tokens)[*i] != D_QUOTE && (*tokens)[*i] != WORD)
			if (nb_of_quotes % 2 == 0)
				break ;
		(*i)++;
	}
	token_quote_replace(tokens, quote, i, first_quote, last_quote);
	//condition d erreure
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
	i = 0;
	while (result[i])
	{
		while (result[i] && result[i] != QUOTE && result[i] != D_QUOTE)
			i++;
		tokenize_quotes(&result, &i);
	}
	return (result);
}
