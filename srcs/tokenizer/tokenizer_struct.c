/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:13:47 by dfeve             #+#    #+#             */
/*   Updated: 2025/03/10 17:59:53 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tokenized	*create_token_struct(char *str)
{
	t_tokenized	*result;

	result = malloc(sizeof(t_tokenized));
	result->tokens = tokenize(str);
	result->split_input = tokenizer_split(str, result->tokens);
	result->tokens = get_tokens(result->split_input, result->tokens);
	result->nb_cmds = tablen(result->split_input);
	return (result);
}

void	free_token_struct(t_tokenized *token)
{
	free_tab(token->split_input);
	free(token->tokens);
	free(token);
}