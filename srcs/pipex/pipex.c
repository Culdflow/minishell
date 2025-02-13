/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:54:38 by gdalmass          #+#    #+#             */
/*   Updated: 2025/02/13 20:15:05 by greg             ###   ########.fr       */
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

char **handle_cmd(char **pipes, char **envp)
{
	//(void)envp;
	
    int i = 0;	
	int	j = 0;
    int fd[3];
    int index[2];
    char	*chevron;
	char	*file;
	char	**cmd;
    
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	fd[2] = 0;
	
    while (pipes[i]) 
		i++;
    cmd = ft_calloc(i + 2, sizeof(char *));
    cmd[i] = NULL;
	
	i = 0;
    while (pipes[i]) {
        chevron = ft_strchr(pipes[i], '<');
        if (chevron)
            index[0] = chevron - pipes[i];
        else
            index[0] = 0;
        
        chevron = ft_strchr(pipes[i], '>');
        if (chevron)
            index[1] = chevron - pipes[i];
        else
            index[1] = ft_strlen(pipes[i]);

        if (index[0]) {
            if (pipes[i][index[0] + 1] == '<') {
            {
				if (fd[0] != 0)
					close(fd[0]);
				fd[0] = -10;
                cmd[j] = sanitize_str(ft_substr(pipes[i], index[0] + 2, index[1]));
				j++;

			}
            } else {
                file = sanitize_str(ft_substr(pipes[i], index[0] + 1, index[1]));
                fd[0] = open(file, O_RDONLY);
                printf("file : %s\n", file);
				if (fd[0] == -1)
				{
					if (access(file, F_OK) != 0)
						fd[2] = 1;
					else
						fd[2] = 2;
				}
                free(file);
            }
        } else {
            if (fd[0] == STDIN_FILENO) {
                if (fd[1] != STDOUT_FILENO)
                    fd[0] = fd[1];
                else
                    fd[0] = STDIN_FILENO;
            }
        }

        if (index[1] != (int)ft_strlen(pipes[i])) 
		{
            file = ft_strtrim(chevron + 1, " ");
            if (pipes[i][index[0]] == '>')
                fd[1] = ft_create_outfile(1, file);
            else
                fd[1] = ft_create_outfile(0, file);
            free(file);
        }
		else
		{
            fd[1] = STDOUT_FILENO;
        }

		


        if (index[0] != 0)
            cmd[j] = sanitize_str(ft_substr(pipes[i], 0, index[0]));
        else
            cmd[j] = sanitize_str(ft_substr(pipes[i], 0, index[1]));
			
		//printf("%s\n", cmd[j]);
        
        j++;

        if (chevron) {
			pipex(j, cmd, envp, fd);
			
			close(fd[0]);
			fd[0] = fd[1];
            
			
			j = 0;
            while (cmd[j]) {
                printf("%s\n", cmd[j]);
                free(cmd[j]);
                j++;
            }
            printf("%d %d\n", fd[0], fd[1]);
            j = 0;
        }
        i++;
    }
	pipex(j, cmd, envp, fd);
	
	
	if (!chevron)
	{
		j = 0;
		while (cmd[j]) {
			printf("%s\n", cmd[j]);
			free(cmd[j]);
			j++;
		}
	}

    close(fd[0]);
    close(fd[1]);
    return cmd;
}

void	parser(char **envp)
{
	(void)envp;

	char *input;
    char **pipes;
	char **cmd;
    int i;

    input = readline(">  ");
    pipes = ft_split(input, '|');


    cmd = handle_cmd(pipes, envp);
    free(input);


	// i = 0;
    // while (cmd[i])
    // {
    //     //printf("%s\n", cmd[i]);
    //     free(cmd[i]);
    //     i++;
    // }
    free(cmd);
    // Libération de `pipes`
    i = 0;
    while (pipes[i])
    {
        free(pipes[i]);
        i++;
    }
    free(pipes);

    // Libération de `cmd` et affichage


	//return (pipex())
}