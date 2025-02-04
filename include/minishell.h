/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:47:00 by dfeve             #+#    #+#             */
/*   Updated: 2025/02/04 19:07:26 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>

typedef enum token
{
	R_DIR_IN,
	R_DIR_OUT,
	PIPE,
	WORD,
}	token;

typedef struct s_tokenized
{
	char	**split_input;
	char	**tokens;
}	t_tokenized;

#endif