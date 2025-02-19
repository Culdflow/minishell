/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:20:23 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/11 14:28:12 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_tolower(int c)
{
	int	result;

	result = c;
	if (c >= 'A' && c <= 'Z')
		result += 32;
	return (result);
}
/*
int main()
{
	printf("%c", (char)ft_tolower('A'));
}*/
