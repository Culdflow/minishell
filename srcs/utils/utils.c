/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:19:37 by dfeve             #+#    #+#             */
/*   Updated: 2025/05/13 19:47:37 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	calculate_my_split_size(t_tokenized *tokenized)
{
	int	result;
	int	cursor;
	int	on_word;

	result = 1;
	cursor = 0;
	on_word = FALSE;
	while (tokenized->split_input && tokenized->split_input[cursor])
	{
		if (tokenized->tokens[cursor] != PIPE)
			on_word = TRUE;
		else if (tokenized->tokens[cursor] == PIPE && on_word == TRUE)
		{
			result++;
			on_word = FALSE;
		}
		cursor++;
	}
	return (result);
}

void	add_el_from_to(t_tokenized *tokenized, int from, int to)
{
	
}

char	**my_split(t_tokenized *tokenized)
{
	char	**result;
	int		on_word;
	int		cursor;

	result = malloc(sizeof(char *) * (calculate_my_split_size(tokenized) + 1));
	cursor = 0;
	on_word = FALSE;
	while (tokenized->split_input && tokenized->split_input[cursor])
	{
		if (tokenized->tokens[cursor] != PIPE)
			on_word = TRUE;
		else if (tokenized->tokens[cursor] == PIPE && on_word == TRUE)
		{
			result++;
			on_word = FALSE;
		}
		cursor++;
	}
}