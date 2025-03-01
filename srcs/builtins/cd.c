/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:07:45 by greg              #+#    #+#             */
/*   Updated: 2025/03/01 13:53:39 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    get_home()
{
    char *home;

    home = getenv("HOME");
    if (!home)
        ft_putstr_fd("cd: HOME not set\n", 2);
    if (chdir(home) != 0)
        perror("cd");
}

void	ft_cd(char **path)
{
    if (path[1] != NULL && path[2] != NULL)
        ft_putstr_fd("cd: too many arguments\n", 2);
    else if (path[1] == NULL || !ft_strcmp(path[1], "~"))
        get_home();
    else if (chdir(path[1]) != 0)
        perror("cd");
}