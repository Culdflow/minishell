/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:21:58 by gdalmass          #+#    #+#             */
/*   Updated: 2025/02/13 18:48:27 by greg             ###   ########.fr       */
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
	char	**cmd_path;
	char	***cmd_args;
	int		here_doc;
	int		append;
	int		fd[2];
	int		exit_code;
	int		cmd_count;
	int		is_invalid_infile;
}	t_pipex;

typedef struct s_prev
{
	int		in;
	int		out;
	int		i;
}	t_prev;

typedef struct s_split
{
	int	count;
	int	i;
	int	j;
}	t_custom_split;

typedef struct s_quotes
{
	int	s_quotes;
	int	d_quotes;
}	t_quotes;

void	parser(char **envp);

void	ft_init_struct(t_pipex *pipex, int nmb, char **cmd, char **envp);
int		ft_here_doc(int fd, char *limiter);
void	ft_error(char *str);
char	**ft_custom_split(char const *s, char c, t_pipex *pipex);
char	**ft_free(char **arr, int j);
size_t	ft_next_occurence(char const *s, char c, int index);
char	*ft_remove_slash(char *str, int len);
int	ft_create_outfile(int here_doc, char *file);
// void	ft_create_outfile(t_pipex *pipex, int ac, char **av);
void	ft_cmd_not_acc(char *name);
void	ft_invalid_cmd(t_pipex *pipex, t_prev *prev);
int		ft_invalid_infile(t_pipex *pipex, t_prev *prev);
void	ft_loop(t_pipex *pipex, t_prev *prev, char **envp);

#endif