/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:54:38 by gdalmass          #+#    #+#             */
/*   Updated: 2025/02/10 19:54:15 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cleanup(t_pipex pipex)
{
	int	i;
	int	j;

	close(pipex.in_fd);
	close(pipex.out_fd);
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
	free(pipex.pids);
	free(pipex.cmd_args);
}

void	ft_wait_children(t_pipex *pipex, t_prev prev, int i)
{
	int		status;

	while (pipex->pids_size > ++i)
	{
		waitpid(pipex->pids[i], &status, 0);
		if (WEXITSTATUS(status))
		{
			if (pipex->pids_size -1 == i)
				pipex->exit_code = WEXITSTATUS(status);
		}
		if (prev.out == -1)
		{
			pipex->exit_code = 1;
		}
	}
}

int	pipex(int nmb, char **cmd, char **envp)
{
	t_pipex	pipex;
	t_prev	prev;
	int		i;

	if (nmb < 3)
		exit(1);
	i = 1;
	while (++i < nmb - 1)
	{
		if (ft_strlen(cmd[i]) == 0)
			exit(1);
	}
	ft_init_struct(&pipex, nmb, cmd, envp);
	if (pipex.here_doc)
		ft_here_doc(pipex.in_fd, cmd[2]);
	prev.in = pipex.in_fd;
	prev.i = -1;
	ft_loop(&pipex, &prev, envp);
	i = -1;
	ft_wait_children(&pipex, prev, i);
	ft_cleanup(pipex);
	return (pipex.exit_code);
}

void	get_next_arg(char *ptr, char *tmp)
{
	int simple;
	int doub;

	simple = 0;
	doub = 0;
	while (*ptr == ' ')
		ptr++;
	while (*ptr != ' ' && !simple && !doub)
	{
		if (*ptr == '\'' )
			simple = ft_abs(simple - 1);
		if (*ptr == '\"')
			simple = ft_abs(doub - 1);

		tmp = ft_strjoin(tmp, ptr);
		ptr++;
	}
}

void	parser(char **envp)
{
	(void)envp;
	char *input;
	char *tmp;
	char **cmds;
	char *ptr;
	int i;

	input = readline(">  ");
	cmds = ft_split(input, '|');
	free(input);
	i = -1;
	while (cmds[++i])
	{
		ptr = ft_strchr(cmds[i], '<');
		if (ptr)
		{
			if (*(ptr++) == '<')
			{
				tmp = ft_strjoin("here_doc ", "");
				get_next_arg(ptr, tmp);
				
			}
			else
			{
				while (*ptr == ' ')
					ptr++;
				while (*ptr != ' ')
				{
					tmp = ft_strjoin(tmp, ptr);
					ptr++;
				}
			}

			
		}
		
	}
	printf("%s\n",input);
	free(input);
	//return (pipex())
}