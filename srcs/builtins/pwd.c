/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:24:18 by greg              #+#    #+#             */
/*   Updated: 2025/02/14 12:51:13 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    pwd(void)
{
    char *cwd;
    
    cwd= getcwd(NULL, 0);
    if (!cwd) {
        perror("getcwd");
        return (1);
    }

    ft_printf("%s\n", cwd);
    free(cwd);

    return (0);
}