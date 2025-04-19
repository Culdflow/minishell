/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:54:42 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/19 18:42:22 by dfeve            ###   ########.fr       */
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
	while (tab && tab[i])
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
	t_token	*tokens_new;
	int		i;
	int		y;

	i = 0;
	y = 0;
	split_input_new = malloc(sizeof(char *) * (clean_split_len(tokenized->split_input) + 1));
	tokens_new = malloc(sizeof(t_token) * (clean_split_len(tokenized->split_input) + 1));
	while (tokenized->split_input && tokenized->split_input[i])
	{
		if (is_only_spaces(tokenized->split_input[i]) == FALSE)
		{
			split_input_new[y] = ft_strtrim(tokenized->split_input[i], " ");
			tokens_new[y] = get_token(split_input_new[y][0]);
			y++;
		}
		i++;
	}
	split_input_new[y] = 0;
	tokens_new[y] = 0;
	free_tab(tokenized->split_input);
	free(tokenized->tokens);
	tokenized->tokens = tokens_new;
	tokenized->split_input = split_input_new;
}

void	add_space(t_tokenized *tokenized)
{
	char	*split_input_new;
	int	i;

	i = 0;
	while (tokenized->split_input && tokenized->split_input[i])
	{
		if (i > 0 && tokenized->tokens[i] == WORD)
		{
			split_input_new = ft_strjoin(" ", tokenized->split_input[i]);
			free(tokenized->split_input[i]);
			tokenized->split_input[i] = split_input_new;
		}
		i++;
	}
}

char	*split_input_join(t_tokenized *tokenized)
{
	char	*result;
	char	*join;
	int	i;

	i = 0;
	result = NULL;
	join = NULL;
	while (tokenized->split_input && tokenized->split_input[i])
	{
		join = ft_strjoin(result, tokenized->split_input[i]);
		if (result)
			free(result);
		result = ft_strdup(join);
		free(join);
		i++;
	}
	return (result);
}