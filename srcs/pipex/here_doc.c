/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:44:44 by gdalmass          #+#    #+#             */
/*   Updated: 2025/04/24 02:43:32 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_get_here_doc_line(int fd, char *limiter)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("heredoc> ");
		printf("out of readline = %s\nlimiter = %s\n", line, limiter);
		if (!line || (ft_strncmp(limiter, line, ft_strlen(limiter)) == 0 && ft_strlen(limiter) == ft_strlen(line)) || manager.SIGINT_RECV == TRUE)
		{
			manager.SIGINT_RECV = FALSE;
			if (line)
				free(line);
			free(limiter);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		free(line);
		line = tmp;
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
}

int	ft_here_doc(int fd, char *limiter)
{
	int	pipe_fd[2];
	int	pid;

	if (pipe(pipe_fd) == -1)
		ft_error("pipe failed");
	pid = fork();
	if (pid == -1)
		ft_error("fork failed");
	if (pid == 0)
	{
		add_pid_l(&manager.pid_list, pid);
		ft_get_here_doc_line(pipe_fd[1], limiter);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], fd) == -1)
			ft_error("dup2 failure");
		close(pipe_fd[0]);
		waitpid(pid, NULL, 0);
	}
	return (pid);
}
