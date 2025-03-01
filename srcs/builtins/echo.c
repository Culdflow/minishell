/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdalmass <gdalmass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:32:37 by greg              #+#    #+#             */
/*   Updated: 2025/02/17 12:38:28 by gdalmass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(char **cmd)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 0;
	while (1)
	{
		if (!ft_strncmp("-n ", &cmd[1][i], 3))
		{
			new_line = 0;
			i += 3;
		}
		else
			break ;
	}
	ft_printf("%s", &cmd[1][i]);
	if (new_line)
		write(1, "\n", 1);
}
