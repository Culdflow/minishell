/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:03:11 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/20 00:03:10 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_sigint(int code)
{
	if (code == -111)
	{
		if (!manager.pid_list)
			exit(130);
		else
			kill(get_last_pid(manager.pid_list)->pid, SIGTERM);
	}
	else
	{
		manager.SIGINT_RECV = TRUE;
		if (!manager.pid_list)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			manager.SIGINT_RECV = FALSE;
		}
		else
			kill(get_last_pid(manager.pid_list)->pid, SIGTERM);
	}
}

void	set_signals()
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	sigaction(SIGINT, &sa, NULL);
}

t_pid_l	*new_pid(int pid)
{
	t_pid_l	*result;

	result = malloc(sizeof(t_pid_l));
	result->pid = pid;
	result->next = NULL;
	return (result);
}

t_pid_l	*get_last_pid(t_pid_l *start)
{
	if (!start)
		return (NULL);
	while (start->next)
		start = start->next;
	return (start);
}

void	add_pid_l(t_pid_l **start, int pid)
{
	t_pid_l	*last;

	last = get_last_pid(*start);
	if (!last)
		*start = new_pid(pid);
	else
		last->next = new_pid(pid);
}

void	free_pid_l(t_pid_l *start)
{
	t_pid_l	*tmp;

	while (start)
	{
		tmp = start->next;
		free(start);
		start = tmp;
	}
}