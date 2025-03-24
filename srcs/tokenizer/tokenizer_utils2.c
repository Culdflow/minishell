/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:54:42 by dfeve             #+#    #+#             */
/*   Updated: 2025/03/18 20:08:04 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_tokens(t_token *tok)
{
	int	i;

	i = -1;
	if (!tok)
		return ;
	while (tok[++i])
		printf("%d", tok[i]);
	printf("\n");
}


void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		printf("%s\n", tab[i++]);
}

int	is_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	clean_split_len(char **tab)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (tab && tab[i])
	{
		if (is_only_spaces(tab[i]) == FALSE)
			size++;
		i++;
	}
	return (size);
}

void	clean_split_input(t_tokenized *tokenized)
{
	char	**split_input_new;
	int		i;
	int		y;

	i = 0;
	y = 0;
	split_input_new = malloc(sizeof(char *) * clean_split_len(tokenized->split_input));
	while (tokenized->split_input && tokenized->split_input[i])
	{
		if (is_only_spaces(tokenized->split_input[i]) == FALSE)
			split_input_new[y++] = ft_strtrim(tokenized->split_input[i], " ");
		i++;
	}
	free_tab(tokenized->split_input);
	tokenized->split_input = split_input_new;
}