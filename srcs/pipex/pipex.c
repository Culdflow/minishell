/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:54:38 by gdalmass          #+#    #+#             */
/*   Updated: 2025/02/14 14:10:31 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cleanup(t_pipex pipex)
{
	int	i;
	int	j;

	// close(pipex.in_fd);
	// close(pipex.out_fd);
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

int	pipex(int nmb, char **cmd, char **envp, int *fd)
{
	t_pipex	pipex;
	t_prev	prev;
	int		i;

	i = 1;
	while (++i < nmb - 1)
	{
		if (ft_strlen(cmd[i]) == 0)
			exit(1);
	}

	pipex.in_fd = fd[0];
	pipex.out_fd = fd[1];
	pipex.is_invalid_infile = fd[2];

	ft_init_struct(&pipex, nmb, cmd, envp);
	if (pipex.here_doc)
		ft_here_doc(pipex.in_fd, cmd[0]);
	prev.in = pipex.in_fd;
	prev.i = -1 + pipex.here_doc;
	ft_loop(&pipex, &prev, envp);
	i = -1;
	ft_wait_children(&pipex, prev, i);
	ft_cleanup(pipex);
	return (pipex.exit_code);
}


char *sanitize_str(char *str) {
    char *trimmed;
	
	if (!str)
		return (NULL);
	trimmed = ft_strtrim(str, " ");
    free(str);
    return trimmed;
}

char *get_chevron_indices(char *pipe, int index[2]) {
    char *chevron;

    chevron = ft_strchr(pipe, '<');
    if (chevron)
        index[0] = chevron - pipe;
    else
        index[0] = 0;
    chevron = ft_strchr(pipe, '>');
    if (chevron)
        index[1] = chevron - pipe;
    else
        index[1] = ft_strlen(pipe);
    return (chevron);
}

int    get_infile(t_parser *info,char **pipes, int i, int j)
{

    if (info->index[0]) {
        if (info->fd[0] != STDIN_FILENO)
                close(info->fd[0]);
        if (pipes[i][info->index[0] + 1] == '<') {
            info->fd[0] = -10;
            info->cmd[j] = sanitize_str(ft_substr(pipes[i], info->index[0] + 2, info->index[1]));
            j++;
        } else {
            info->files[0] = sanitize_str(ft_substr(pipes[i], info->index[0] + 1, info->index[1]));
            info->fd[0] = open(info->files[0], O_RDONLY);
            if (info->fd[0] == -1) {
                if (access(info->files[0], F_OK) != 0)
                    info->fd[2] = 1;
                else
                    info->fd[2] = 2;
            }
        }
    }

    return (j);
}

void    get_outfile(t_parser *info, char **pipes, int i)
{
    if (info->index[1] != (int)ft_strlen(pipes[i])) {
        if (pipes[i][info->index[1] + 1] == '>')
        {
            info->files[1] = ft_strtrim(info->chevron + 2, " ");
            info->fd[1] = ft_create_outfile(1, info->files[1]);
        }
        else
        {
            info->files[1] = ft_strtrim(info->chevron + 1, " ");
            info->fd[1] = ft_create_outfile(0, info->files[1]);
        }
    } else {
        info->fd[1] = STDOUT_FILENO;
    }
}

void    init_parser_struct(t_parser *info, char **pipes)
{
    int i;

    i = 0;
    info->fd[0] = STDIN_FILENO;
    info->fd[1] = STDOUT_FILENO;
    info->fd[2] = 0;
    while (pipes[i]) 
        i++;
    info->cmd = ft_calloc(i + 2, sizeof(char *));
}

void    clean_after_pipex(t_parser *info)
{
    if (info->fd[0] != STDIN_FILENO)
        close(info->fd[0]);
    if (info->fd[1] != STDOUT_FILENO)
        close(info->fd[1]);
    info->fd[0] = open(info->files[1], O_RDWR);
}

int exec_pipex(int *j, t_parser *info, char **envp)
{
    int i;
    int code;

    code = pipex(*j, info->cmd, envp, info->fd);
    *j = 0;
    clean_after_pipex(info);
    i = 0;
    while (info->cmd[i])
    {
        free(info->cmd[i]);
        info->cmd[i] = NULL;
        i++;
    }
    return (code);
}

void    clean_handle_cmd(t_parser *info)
{
    int j;

    j = -1;
    while (info->cmd[++j])
        free(info->cmd[j]);
    free(info->cmd);
    close(info->fd[0]);
    close(info->fd[1]);
}

int    get_files(t_parser *info, int i, int j, char **pipes)
{
    info->files[0] = NULL;
    info->files[1] = NULL;
    info->chevron = get_chevron_indices(pipes[i], info->index);
    if (info->chevron)
        info->index[1] = info->chevron - pipes[i];
    else
        info->index[1] = ft_strlen(pipes[i]);
    j = get_infile(info, pipes, i, j);
    get_outfile(info, pipes, i);
    return (j);
}

void    get_cmd(t_parser *info, char **pipes, int i, int j)
{
    if (info->index[0] != 0)
        info->cmd[j] = sanitize_str(ft_substr(pipes[i], 0, info->index[0]));
    else
        info->cmd[j] = sanitize_str(ft_substr(pipes[i], 0, info->index[1]));
}


int	parser(char **pipes, char **envp)
{
    t_parser info;
    int i ;
    int j;
    
    init_parser_struct(&info, pipes);
    i = 0;
    j = 0;
    while (pipes[i]) {
        j = get_files(&info, i, j, pipes);
        get_cmd(&info, pipes, i, j);
        j++;
        if (info.chevron)
            info.res = exec_pipex(&j, &info, envp);
        i++;
		if (info.files[0])
			free(info.files[0]);
		if (info.files[1])
			free(info.files[1]);
    }
    if (!info.chevron)
        info.res = pipex(j, info.cmd, envp, info.fd);
    clean_handle_cmd(&info);
    return (info.res);
}


int	handle_cmd(char **envp)
{
	char *input;
    char **pipes;
    int i;
    int code;

    input = readline(">  ");
    pipes = ft_split(input, '|');


    code = parser(pipes, envp);
    free(input);

    i = 0;
    while (pipes[i])
    {
        free(pipes[i]);
        i++;
    }
    free(pipes);
    return (code);
}