/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:46:40 by dfeve             #+#    #+#             */
/*   Updated: 2025/03/01 13:53:49 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_minish manager;

	(void)ac;
	(void)av;
	// (void)envp;

    printf("CHECK IF WE NEED TO ADD '~' and '-'\n\n");


	printf("TEST TO HANDLE : \n");
	printf("echo ff > | echo nope \n");
	while (1)
		manager.last_ex_code = handle_cmd(envp, &manager);

	// pwd();

	// t_tokenized	*toeknized;

	// toeknized = create_token_struct("\"hello\"oh\"cuntass\"");
	// print_tab(toeknized->split_input);
	// print_tokens(toeknized->tokens);
	// free_token_struct(toeknized);
}