/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:13:47 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/12 01:54:32 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_rdir(t_tokenized *tokenized)
{
	int	i;

	i = 0;
	while (tokenized->split_input && tokenized->split_input[i])
	{
		if ((ft_strlen(tokenized->split_input[i]) > 2)
			&& (tokenized->tokens[i] == R_DIR_IN
				|| tokenized->tokens[i] == R_DIR_OUT))
				printf("ERROR: RDIR TOO MANY > OR <\n");
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
	char		*join_split_input;

	result = malloc(sizeof(t_tokenized));
	result->tokens = tokenize(str);
	result->split_input = tokenizer_split(str, result->tokens);
	result->tokens = get_tokens(result->split_input, result->tokens);
	clean_split_input(result);
	check_rdir(result);
	print_tab(result->split_input);
	result->fd[0] = parget_infile(result);
	result->fd[1] = parget_outfile(result);
	join_split_input = split_input_join(result);
	printf("join split input = %s\n", join_split_input);
	remove_char_str(&join_split_input, '\a');
	free_tab(result->split_input);
	result->split_input = ft_split(join_split_input, '|');
	free(join_split_input);
	result->nb_cmds = tablen(result->split_input);
	return (result);
}

void	free_token_struct(t_tokenized *token)
{
	free_tab(token->split_input);
	free(token->tokens);
	if (token->fd[0] > 1)
		close(token->fd[0]);
	if (token->fd[1] > 1)
		close(token->fd[1]);
	free(token);
}