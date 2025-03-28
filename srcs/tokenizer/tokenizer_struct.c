/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:13:47 by dfeve             #+#    #+#             */
/*   Updated: 2025/03/24 15:28:54 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_rdir(t_tokenized *tokenized)
{
	int	i;

	i = 0;
	while (tokenized->split_input[i])
	{
		if ((ft_strlen(tokenized->split_input[i]) > 2)
			&& (tokenized->tokens[i] == R_DIR_IN
				|| tokenized->tokens[i] == R_DIR_OUT))
			// ERROR HANDLING
			if (ft_strlen(tokenized->split_input[i]) == 2)
			{
				if (tokenized->tokens[i] == R_DIR_IN)
					tokenized->tokens[i] = RR_DIR_IN;
				else if (tokenized->tokens[i] == R_DIR_OUT)
					tokenized->tokens[i] = RR_DIR_OUT;
			}
		i++;
	}
}

t_tokenized	*create_token_struct(char *str)
{
	t_tokenized	*result;

	result = malloc(sizeof(t_tokenized));
	result->tokens = tokenize(str);
	result->split_input = tokenizer_split(str, result->tokens);
	result->tokens = get_tokens(result->split_input, result->tokens);
	check_rdir(result);
	result->nb_cmds = tablen(result->split_input);
	return (result);
}

void	free_token_struct(t_tokenized *token)
{
	free_tab(token->split_input);
	free(token->tokens);
	free(token);
}