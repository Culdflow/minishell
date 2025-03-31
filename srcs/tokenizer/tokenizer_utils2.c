/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:54:42 by dfeve             #+#    #+#             */
/*   Updated: 2025/03/31 18:19:12 by dfeve            ###   ########.fr       */
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
	split_input_new = malloc(sizeof(char *) * (clean_split_len(tokenized->split_input) + 1));
	while (tokenized->split_input && tokenized->split_input[i])
	{
		printf("split_input = %s\n", tokenized->split_input[i]);
		if (is_only_spaces(tokenized->split_input[i]) == FALSE)
		{
			printf("is not only spaces\n");
			split_input_new[y++] = ft_strtrim(tokenized->split_input[i], " ");
			printf("turned to this %s\n", split_input_new[y - 1]);
		}
		i++;
	}
	split_input_new[y] = 0;
	free_tab(tokenized->split_input);
	tokenized->split_input = split_input_new;
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
		printf("joining %s and %s\n", result, tokenized->split_input[i]);
		join = ft_strjoin(result, tokenized->split_input[i]);
		if (result)
			free(result);
		printf("resulted in %s\n", join);
		result = ft_strdup(join);
		free(join);
		i++;
	}
	return (result);
}