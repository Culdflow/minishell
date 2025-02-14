/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:46:40 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/14 14:03:12 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{

	(void)ac;
	(void)av;
	// (void)envp;
	handle_cmd(envp);
	
	
	// pwd();



	// t_tokenized	*toeknized;

	// toeknized = create_token_struct("\"hello\"oh\"cuntass\"");
	// print_tab(toeknized->split_input);
	// print_tokens(toeknized->tokens);
	// free_token_struct(toeknized);
}