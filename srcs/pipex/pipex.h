/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:21:58 by gdalmass          #+#    #+#             */
/*   Updated: 2025/03/10 15:40:18 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define VAR_FILE "t.txt"

typedef struct s_pipex
{
	int		*pids;
	int		pids_size;
	int		in_fd;
	int		out_fd;
	char	**envp;
	char	**cmd_path;
	char	***cmd_args;
	int		here_doc;
	int		append;
	int		fd[2];
	int		exit_code;
	int		cmd_count;
	int		is_invalid_infile;
	int		exit;
}			t_pipex;

typedef struct s_prev
{
	int		in;
	int		out;
	int		i;
}			t_prev;

typedef struct s_split
{
	int		count;
	int		i;
	int		j;
}			t_custom_split;

typedef struct s_quotes
{
	int		s_quotes;
	int		d_quotes;
}			t_quotes;

typedef struct s_parser
{
	int		res;
	int		fd[3];
	int		index[2];
	char	*chevron;
	char	*files[2];
	char	**cmd;
	int		cmd_nb;
}			t_parser;

void		ft_cleanup(t_pipex pipex);

void		ft_init_struct(t_pipex *pipex, int nmb, char **cmd, char **envp);
int			ft_here_doc(int fd, char *limiter);
void		ft_error(char *str);
char		**ft_custom_split(char const *s, char c, t_pipex *pipex);
char		**ft_free(char **arr, int j);
size_t		ft_next_occurence(char const *s, char c, int index);
char		*ft_remove_slash(char *str, int len);
int			ft_create_outfile(int here_doc, char *file);
void		ft_invalid_cmd(t_pipex *pipex, t_prev *prev);
int			ft_invalid_infile(t_pipex *pipex, t_prev *prev);
void		ft_loop(t_pipex *pipex, t_prev *prev, char **envp);
int			pipex(int nmb, char **cmd, char **envp, int *fd);
int			exec_pipex(int *j, t_parser *info, char **envp);
void		init_parser_struct(t_parser *info, char **pipes, int pipe_nb);
char		*sanitize_str(char *str);
char		*get_chevron_indices(char *pipe, int index[2]);
int		get_outfile(t_parser *info, char **pipes, int i);
int			get_infile(t_parser *info, char **pipes, int i, int j);
int			is_builtins(char *str);

#endif