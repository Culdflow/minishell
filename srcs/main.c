/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:46:40 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/25 23:22:36 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_tokenized	*toeknized;

	(void)argc;
	(void)argv;
	toeknized = create_token_struct("$_");
	print_tab(toeknized->split_input);
	print_tokens(toeknized->tokens);
	expand(toeknized, env);
	print_tab(toeknized->split_input);
	free_token_struct(toeknized);
}