/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 03:01:25 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/15 03:30:18 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_parerror(char *error_msg, t_tokenized *tokenized)
{
	ft_putstr_fd(error_msg, 2);
	free_tab(tokenized->split_input);
	tokenized->split_input = NULL;
}