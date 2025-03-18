/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:46:40 by dfeve             #+#    #+#             */
/*   Updated: 2025/03/19 00:15:16 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_tokenized	*toeknized;

	(void)argc;
	(void)argv;
	toeknized = create_token_struct("$1ahahaha$hey$USER << hello");
	print_tab(toeknized->split_input);
	print_tokens(toeknized->tokens);
	expand(toeknized, &env, env);
	print_tab(toeknized->split_input);
	printf("nb commands = %d\n", toeknized->nb_cmds);
	free_token_struct(toeknized);
}