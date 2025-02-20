/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:54:38 by gdalmass          #+#    #+#             */
/*   Updated: 2025/02/20 14:34:23 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cleanup(t_pipex pipex)
{
	int	i;
	int	j;

	// close(pipex.in_fd);
	// close(pipex.out_fd);
	free(pipex.pids);
	if (pipex.here_doc)
		unlink("here_doc.txt");
	i = -1;
	while (pipex.cmd_args[++i])
	{
		j = -1;
		free(pipex.cmd_path[i]);
		while (pipex.cmd_args[i][++j])
			free(pipex.cmd_args[i][j]);
		free(pipex.cmd_args[i]);
	}
	free(pipex.cmd_path);
	free(pipex.cmd_args);
}

void	ft_wait_children(t_pipex *pipex, t_prev prev, int i)
{
	int	status;

	while (pipex->pids_size > ++i)
	{
		waitpid(pipex->pids[i], &status, 0);
		if (WEXITSTATUS(status))
		{
			if (pipex->pids_size - 1 == i)
				pipex->exit_code = WEXITSTATUS(status);
		}
		if (prev.out == -1)
		{
			pipex->exit_code = 1;
		}
	}
}

int	pipex(int nmb, char **cmd, char **envp, int *fd)
{
	t_pipex	pipex;
	t_prev	prev;
	int		i;

	// printf("===============\n");
	// printf("PLS CHECK : echo ff > txt | echo nope\n");
	// i = -1;
	// printf("fd : %d %d\n", fd[0], fd[1]);
	// while (cmd[++i])
	// {
	// 	printf("cmd : %s\n", cmd[i]);
	// }
	i = 1;
	while (++i < nmb - 1)
	{
		if (ft_strlen(cmd[i]) == 0)
			exit(1);
	}
	pipex.in_fd = fd[0];
	pipex.out_fd = fd[1];
	pipex.is_invalid_infile = fd[2];
	pipex.envp = envp;
	ft_init_struct(&pipex, nmb, cmd, envp);
	if (pipex.here_doc)
		ft_here_doc(pipex.in_fd, cmd[0]);
	prev.in = pipex.in_fd;
	prev.i = -1 + pipex.here_doc;
	ft_loop(&pipex, &prev, envp);
	i = -1;
	ft_wait_children(&pipex, prev, i);
	ft_cleanup(pipex);
	if (pipex.exit)
		exit(1);
	return (pipex.exit_code);
}
