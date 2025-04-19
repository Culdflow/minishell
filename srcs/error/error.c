/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 03:01:25 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/19 19:14:43 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_parerror(char *filename, t_tokenized *tokenized)
{
	perror(filename);
	free_tab(tokenized->split_input);
	tokenized->split_input = NULL;
}