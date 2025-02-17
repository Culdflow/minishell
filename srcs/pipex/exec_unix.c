/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:54:13 by greg              #+#    #+#             */
/*   Updated: 2025/02/17 16:18:24 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exec_child(t_prev prev, t_pipex *pip, int i, char **envp)
{
	dup2(prev.in, STDIN_FILENO);
	dup2(prev.out, STDOUT_FILENO);
	if (!ft_strncmp(pip->cmd_args[i][0], "pwd", 3))
		pwd();
	else if (!ft_strncmp(pip->cmd_args[i][0], "env", 3))
		ft_env(pip);
	else if (!ft_strncmp(pip->cmd_args[i][0], "echo", 4))
		ft_echo(pip->cmd_args[i]);
	else if (!ft_strncmp(pip->cmd_args[i][0], "exit", 4))
		;
	else if (execve(pip->cmd_path[i], pip->cmd_args[i], envp) == -1)
	{
		ft_cmd_not_acc(pip->cmd_args[i][0]);
		write(prev.out, "\0", 1);
		if (prev.i == pip->cmd_count - 1)
		{
			if (pip->cmd_path[i] == NULL)
				exit(127);
			else
				exit(1);
		}
	}
}

void	ft_exec(t_prev prev, t_pipex *pip, int i, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork failed");
	if (pid == 0)
	{
		ft_exec_child(prev, pip, i, envp);
	}
	pip->pids_size++;
	pip->pids = ft_realloc(pip->pids, (pip->pids_size) * sizeof(int),
			(pip->pids_size + 1) * sizeof(int));
	pip->pids[pip->pids_size - 1] = pid;
}

void	ft_manage_exec(t_pipex *pipex, t_prev *prev, char **envp)
{
	if (prev->i == pipex->cmd_count - 1)
		prev->out = pipex->out_fd;
	else
		prev->out = pipex->fd[1];
	ft_exec(*prev, pipex, prev->i, envp);
}

int	ft_is_skippable(t_pipex *pipex, t_prev *prev)
{
	if ((!ft_strncmp(pipex->cmd_args[prev->i][0], "cat", 3)
			&& prev->i != pipex->cmd_count - 1
			&& pipex->cmd_args[prev->i][1] == NULL
			&& ft_strncmp(pipex->cmd_args[prev->i + 1][0], "wc", 2)))
		return (1);
	return (0);
}

void	ft_loop(t_pipex *pipex, t_prev *prev, char **envp)
{
	while (++prev->i < pipex->cmd_count)
	{
		if (!ft_strncmp(pipex->cmd_args[prev->i][0], "exit", 4))
			pipex->exit = 1;
		if (pipe(pipex->fd) == -1)
			ft_error("pipe failed");
		if (prev->in == -1 && pipex->is_invalid_infile > 0)
		{
			if (ft_invalid_infile(pipex, prev) == -1)
				break ;
		}
		else if (pipex->cmd_path[prev->i] == NULL
			&& !is_builtins(pipex->cmd_args[prev->i][0]))
		{
			ft_invalid_cmd(pipex, prev);
			prev->in = pipex->fd[0];
			continue ;
		}
		else if (ft_is_skippable(pipex, prev))
			continue ;
		else
			ft_manage_exec(pipex, prev, envp);
		close(pipex->fd[1]);
		if (prev->in != pipex->in_fd)
			close(prev->in);
		prev->in = pipex->fd[0];
	}
}
