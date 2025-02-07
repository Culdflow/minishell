/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:42:37 by gdalmass          #+#    #+#             */
/*   Updated: 2025/02/07 17:49:42 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_get_cmd_path(char **arr, char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (arr[i])
	{
		tmp = ft_strjoin("/", cmd);
		path = ft_strjoin(arr[i], tmp);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*ft_get_path_env(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	if (!envp[i])
		return ("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path);
}

void	ft_init_first(t_pipex *pipex, int ac, char **av)
{
	int		fd;

	pipex->here_doc = !ft_strncmp(av[1], "here_doc", 8);
	if (pipex->here_doc)
		fd = open("here_doc.txt", O_RDWR | O_CREAT, 0666);
	else
		fd = open(av[1], O_RDONLY);
	pipex->in_fd = fd;
	if (fd == -1)
	{
		if (access(av[1], F_OK) != 0)
			pipex->is_invalid_infile = 1;
		else
			pipex->is_invalid_infile = 2;
	}
	else
		pipex->is_invalid_infile = 0;
	ft_create_outfile(pipex, ac, av);
	pipex->exit_code = 0;
	pipex->pids_size = 0;
	pipex->pids = malloc(sizeof(int));
}

void	ft_init_second(t_pipex *pip, int ac, char **av, char **envp)
{
	int		i;
	char	**path_arr;

	pip->cmd_count = ac - (3 + pip->here_doc);
	path_arr = ft_split(ft_get_path_env(envp), ':');
	pip->cmd_args = malloc((pip->cmd_count + 1) * sizeof(char **));
	pip->cmd_path = malloc((pip->cmd_count + 1) * sizeof(char *));
	pip->cmd_args[pip->cmd_count] = NULL;
	pip->cmd_path[pip->cmd_count] = NULL;
	i = -1;
	while (++i < (pip->cmd_count))
	{
		pip->cmd_args[i] = ft_custom_split(av[i + 2 + pip->here_doc], 32, pip);
		pip->cmd_path[i] = ft_get_cmd_path(path_arr, pip->cmd_args[i][0]);
	}
	i = -1;
	while (path_arr[++i])
		free(path_arr[i]);
	free(path_arr);
}

void	ft_init_struct(t_pipex *pipex, int ac, char **av, char **envp)
{
	ft_init_first(pipex, ac, av);
	ft_init_second(pipex, ac, av, envp);
}
