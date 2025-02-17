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
	int		new_line;
	char	**tmp;
	int		i;

	new_line = 1;
	if (!ft_strncmp("-n ", cmd[1], 3))
	{
		new_line = 0;
		tmp = ft_nsplit(cmd[1], ' ', 1);
		ft_printf("%s", tmp[1]);
		i = 0;
		free(tmp[0]);
		free(tmp[1]);
		free(tmp);
		return ;
	}
	ft_printf("%s", cmd[1]);
	if (new_line)
		write(1, "\n", 1);
}
