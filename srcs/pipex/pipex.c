/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:54:38 by gdalmass          #+#    #+#             */
/*   Updated: 2025/02/14 12:23:12 by greg             ###   ########.fr       */
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

int check_fd(int fd) {
    char buffer[1024];
    ssize_t bytes_read;

    if (fd == -1) {
        printf("File descriptor is invalid\n");
        return 0;
    }

    // Try to read a byte from the file descriptor
    bytes_read = read(fd, buffer, 1);
    if (bytes_read == -1) {
        // If read failed, print an error and return false
        perror("Error reading from fd");
        return 0;
    } else if (bytes_read == 0) {
        // If we couldn't read any data (EOF), it might indicate empty input
        printf("EOF reached on fd\n");
        return 0;
    } else {
        // Successfully read data
        printf("Successfully read from fd: %c\n", buffer[0]);
        return 1;
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

	// printf("pipex :%d %d\n", fd[0], fd[1]);
	// printf("pipex :%s\n", cmd[0]);

	// if (!check_fd(fd[0])) {
    //     // Handle the case when fd[0] doesn't have data or is invalid
    //     printf("Error: Input file descriptor does not contain expected data.\n");
    //     return -1;
    // }

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

int	handle_cmd(char **pipes, char **envp)
{
    int i = 0;
    int j = 0;
    int res = 0;
    int fd[3];
    int index[2];
    char *chevron;
    char *files[2];
    char **cmd;
    
    fd[0] = STDIN_FILENO;
    fd[1] = STDOUT_FILENO;
    fd[2] = 0;
    
    while (pipes[i]) 
        i++;
    
    cmd = ft_calloc(i + 2, sizeof(char *));
    cmd[i] = NULL;

    
    i = 0;
    while (pipes[i]) {
		files[0] = NULL;
		files[1] = NULL;

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
			if (fd[0] != STDIN_FILENO)
                    close(fd[0]);
            if (pipes[i][index[0] + 1] == '<') {
                fd[0] = -10;
                cmd[j] = sanitize_str(ft_substr(pipes[i], index[0] + 2, index[1]));
                j++;
            } else {
                files[0] = sanitize_str(ft_substr(pipes[i], index[0] + 1, index[1]));
                fd[0] = open(files[0], O_RDONLY);
                // printf("file : %s\n", files[0]);
                if (fd[0] == -1) {
                    if (access(files[0], F_OK) != 0)
                        fd[2] = 1;
                    else
                        fd[2] = 2;
                }
            }
        }

        if (index[1] != (int)ft_strlen(pipes[i])) {
            // Output redirection
            if (pipes[i][index[1] + 1] == '>')
			{
				files[1] = ft_strtrim(chevron + 2, " ");
                fd[1] = ft_create_outfile(1, files[1]);
			}
            else
            {
				files[1] = ft_strtrim(chevron + 1, " ");
				fd[1] = ft_create_outfile(0, files[1]);
			}
        } else {
            fd[1] = STDOUT_FILENO;
        }

        if (index[0] != 0)
            cmd[j] = sanitize_str(ft_substr(pipes[i], 0, index[0]));
        else
            cmd[j] = sanitize_str(ft_substr(pipes[i], 0, index[1]));
        
        j++;

        if (chevron) {
            // Execute the command with the updated fd
            pipex(j, cmd, envp, fd);
            
            // Update fd for the next command in the pipeline
            if (fd[0] != STDIN_FILENO)
                close(fd[0]);
			if (fd[1] != STDOUT_FILENO)
				close(fd[1]);
			fd[0] = open(files[1], O_RDWR);


            // Clean up the command array
            j = 0;
            while (cmd[j]) {
                // printf("%s\n", cmd[j]);
                free(cmd[j]);
                cmd[j] = NULL;
                j++;
            }

            // printf("%d %d\n", fd[0], fd[1]);
            j = 0;
        }
        i++;
		if (files[0])
			free(files[0]);
		if (files[1])
			free(files[1]);
    }

    res = pipex(j, cmd, envp, fd);

    // Final clean-up
    j = 0;
    while (cmd[j]) {
        //printf("%s\n", cmd[j]);
        free(cmd[j]);
        j++;
    }
    free(cmd);

    close(fd[0]);
    close(fd[1]);
    return (res);
}


void	parser(char **envp)
{
	(void)envp;

	char *input;
    char **pipes;
    int i;

    input = readline(">  ");
    pipes = ft_split(input, '|');


    handle_cmd(pipes, envp);
    free(input);

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