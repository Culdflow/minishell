/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:47:00 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/12 01:45:58 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <libft.h>
# include <limits.h>
# include <pipex.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>

typedef struct s_minish
{
	int		last_ex_code;
	char	*last_cmd;
	char	**envp;
}			t_minish;

typedef struct s_outfile
{
	int					is_append;
	char				*file;
	struct s_outfile	*next;
}	t_outfile;

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
}			t_token;

typedef struct s_tokenized
{
	int		nb_cmds;
	char	**split_input;
	t_token	*tokens;
	int		fd[3];
}			t_tokenized;

int			pwd(void);
void		ft_env(t_pipex *pip);
void		ft_echo(char **cmd);
void		ft_cd(char **path);
int			handle_cmd(char **envp, t_minish *manager);

/////////////////---TOKENIZER---////////////////////////

void		print_tokens(t_token *tok);
t_token		*tokenize(char *str);
void		free_tokens(t_token *tokens);
int			get_split_size(t_token *tokens);
char		**tokenizer_split(char *str, t_token *tokens);
void		print_tab(char **tab);
void		free_tab(char **tab);
t_token		get_token(char c);
t_token		*get_tokens(char **split, t_token *tokens);
int			strlen_tokens(t_token *tokens, int *i);
t_tokenized	*create_token_struct(char *str);
void		free_token_struct(t_tokenized *token);
void		clean_split_input(t_tokenized *tokenized);
char		*split_input_join(t_tokenized *tokenized);

/////////////////---EXPANDER---////////////////////////

void		expand(t_tokenized *tokenized, char ***env, char **real_env);

void		ft_export(char ***env, char *str);

int			tablen(char **tab);

char		*get_in_env(char ***env, char **str, int expand_size,
				char **real_env);
char		**copy_env(char **env);
void		remove_char_str(char **str, char rm_char);

/////////////////---OUTFILE---////////////////////////

t_outfile	*add_outfile(t_outfile *start, char *fileName, int is_append);
t_outfile	*get_last_outfile(t_outfile *start);
int			parget_outfile(t_tokenized *tokenized);
int			parget_infile(t_tokenized *tokenized);
void		free_outfiles(t_outfile *outfiles);
#endif