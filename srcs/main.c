/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:46:40 by dfeve             #+#    #+#             */
/*   Updated: 2025/03/31 17:54:44 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	// t_minish manager;

	// (void)ac;
	// (void)av;

	// printf("TEST TO HANDLE : \n");
	// printf("echo ff > | echo nope \n");
	// manager.envp = copy_env(envp);
	// while (1)
	// 	manager.last_ex_code = handle_cmd(envp, &manager);

	// pwd();

	t_tokenized	*toeknized;
	int	infile;
	int	outfile;
	char *buf;
	(void)ac;
	(void)av;
	(void)envp;
	
	buf = NULL;
	printf("start\n");
	toeknized = create_token_struct("< a.txt >c.txt > b.txt waa | babes");
	printf("tokenized\n");
	infile = toeknized->fd[0];
	printf("got infile = %d\n", infile);
	outfile = toeknized->fd[1];
	printf("got outfile = %d\n", outfile);
	buf = get_next_line(infile);
	printf("%s\n", buf);
	free(buf);
	write(outfile, "lol", 3);
	print_tab(toeknized->split_input);
	print_tokens(toeknized->tokens);
	free_token_struct(toeknized);
}