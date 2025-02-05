/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:47:00 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/05 14:27:44 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>

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

void	print_tokens(t_token *tok);
t_token	*tokenize(char *str);
void	free_tokens(t_token *tokens);
int		get_split_size(t_token *tokens);
char	**tokenizer_split(char *str);
void	print_tab(char **tab);
void	free_tab(char **tab);
t_token	get_token(char c);
t_token	*get_tokens(char **split);
int		strlen_tokens(t_token *tokens, int	*i);
#endif