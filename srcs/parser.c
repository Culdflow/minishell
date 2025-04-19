/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:15:38 by greg              #+#    #+#             */
/*   Updated: 2025/04/20 00:04:35 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_handle_cmd(t_parser *info)
{
	int	j;

	j = -1;
	while (info->cmd[++j])
		free(info->cmd[j]);
	free(info->cmd);
	if (info->fd[0] != STDIN_FILENO)
		close(info->fd[0]);
	if (info->fd[1] != STDOUT_FILENO)
		close(info->fd[1]);
}

int	get_files(t_parser *info, int i, int j, char **pipes)
{
	info->files[0] = NULL;
	info->files[1] = NULL;
	info->chevron = get_chevron_indices(pipes[i], info->index);
	if (info->chevron)
		info->index[1] = info->chevron - pipes[i];
	else
		info->index[1] = ft_strlen(pipes[i]);
	j = get_infile(info, pipes, i, j);
	if (get_outfile(info, pipes, i) == -1)
		return (-1);
	return (j);
}

void	get_cmd(t_parser *info, char **pipes, int i, int j)
{
	if (info->index[0] != 0)
		info->cmd[j] = sanitize_str(ft_substr(pipes[i], 0, info->index[0]));
	else
		info->cmd[j] = sanitize_str(ft_substr(pipes[i], 0, info->index[1]));
}

int	parser(t_tokenized *tokenized, char **envp)
{
	t_parser	info;
	int			i;
	int			j;

	init_parser_struct(&info, tokenized->split_input, tokenized->nb_cmds, tokenized->fd);
	i = 0;
	j = 0;
	while (tokenized->split_input && tokenized->split_input[i])
	{
		j = get_files(&info, i, j, tokenized->split_input);
		if (j == -1)
		{
			free(info.cmd);
			return (2);
		}
		get_cmd(&info, tokenized->split_input, i, j);
		j++;
		if (info.chevron)
			info.res = exec_pipex(&j, &info, envp);
		i++;
		if (info.files[0])
			free(info.files[0]);
		if (info.files[1])
			free(info.files[1]);
	}
	info.fd[0] = tokenized->fd[0];
	info.fd[1] = tokenized->fd[1];
	if (!info.chevron)
		info.res = pipex(j, info.cmd, envp, info.fd);
	clean_handle_cmd(&info);
	return (info.res);
}

int	get_pipe_count(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

int	handle_cmd(char **envp, t_minish *manager)
{
	t_tokenized	*tokenized;
	char	*input;
	int		code;

	// rl_replace_line("", 0);
	// rl_redisplay();
	input = readline(">  ");
	if (manager->SIGINT_RECV == TRUE)
	{
		manager->SIGINT_RECV = FALSE;
		handle_cmd(envp, manager);
	}
	// if (!input)
	// 	handle_sigint(-111);
	if (*input && ft_strcmp(input, manager->last_cmd) != 0)
		add_history(input);
	
	
		// TO DO : ENV VAR + $?
	tokenized = create_token_struct(input);
	expand(tokenized, &manager->envp, envp);
	code = parser(tokenized , envp);
	free_token_struct(tokenized);
	free(input);
	return (code);
}
