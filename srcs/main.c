/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:46:40 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/05 17:03:18 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main()
{
	char	*str = "hello | \"||>>,<<\" | \"hello\"";
	printf("%s\n", str);
	char	**split;
	t_token	*tokens;

	tokens = tokenize(str);
	split = tokenizer_split(str, tokens);
	print_tab(split);
	print_tokens(tokens);
	tokens = get_tokens(split, tokens);
	print_tokens(tokens);
	free_tab(split);
	free(tokens);
}