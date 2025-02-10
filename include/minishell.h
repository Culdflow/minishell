/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:47:00 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/10 18:14:39 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>
# include <pipex.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>

typedef enum e_token
{
	INVALID = -1,
	WORD = 1,
	PIPE,
	AND,
	OR,
	VAR,
	QUOTE,
	D_QUOTE,
	R_DIR_OUT,
	R_DIR_IN,
	RR_DIR_OUT,
	RR_DIR_IN,
}	t_token;

typedef struct s_tokenized
{
	char	**split_input;
	t_token	*tokens;
}	t_tokenized;

void		print_tokens(t_token *tok);
t_token		*tokenize(char *str);
void		free_tokens(t_token *tokens);
int			get_split_size(t_token *tokens);
char		**tokenizer_split(char *str, t_token *tokens);
void		print_tab(char **tab);
void		free_tab(char **tab);
t_token		get_token(char c);
t_token		*get_tokens(char **split, t_token *tokens);
int			strlen_tokens(t_token *tokens, int	*i);
t_tokenized	*create_token_struct(char *str);
void		free_token_struct(t_tokenized *token);
#endif