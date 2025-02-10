/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greg <greg@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:08:24 by gdalmass          #+#    #+#             */
/*   Updated: 2025/02/10 18:10:10 by greg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	ft_next_occurence(char const *s, char c, int index)
{
	t_quotes	quotes;

	quotes.s_quotes = 0;
	quotes.d_quotes = 0;
	while (s[index])
	{
		if (s[index] == '\'' && (index == 0 || s[index - 1] != '\\'))
			quotes.s_quotes = !quotes.s_quotes;
		if (s[index] == '\"' && (index == 0 || s[index - 1] != '\\'))
			quotes.d_quotes = !quotes.d_quotes;
		if (!quotes.s_quotes && !quotes.d_quotes && s[index] == c)
			break ;
		index++;
	}
	return ((size_t)index);
}

char	**ft_free(char **arr, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	*ft_remove_slash(char *str, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str || len <= 0)
		return (str);
	while (i < len)
	{
		if (str[i] == '\\' && (str[i + 1] == '\''
				|| str[i + 1] == '\"' || str[i + 1] == '\\'))
			i++;
		if (i < len)
			str[j++] = str[i++];
	}
	str[j] = '\0';
	return (str);
}

void	ft_create_outfile(t_pipex *pipex, int ac, char **av)
{
	int	fd;

	if (pipex->here_doc)
		fd = open(av[ac - 1], O_RDWR | O_APPEND);
	else
		fd = open(av[ac - 1], O_RDWR | O_TRUNC);
	if (fd == -1)
	{
		if (pipex->here_doc)
			fd = open(av[ac - 1], O_RDWR | O_APPEND | O_CREAT, 0666);
		else
			fd = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	}
	pipex->out_fd = fd;
}

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
