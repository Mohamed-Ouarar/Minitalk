/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utlis_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarar <mouarar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:55:15 by mouarar           #+#    #+#             */
/*   Updated: 2025/02/16 17:04:31 by mouarar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	character_size(unsigned char c)
{
	if (c < 0b10000000)
		return (1);
	else if ((c & 0b11100000) == 0b11000000)
		return (2);
	else if ((c & 0b11110000) == 0b11100000)
		return (3);
	else if ((c & 0b11111000) == 0b11110000)
		return (4);
	return (0);
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

void	print_pid(unsigned long long num)
{
	char	number;

	if (num > 9)
	{
		print_pid(num / 10);
		print_pid(num % 10);
	}
	else
	{
		number = num + 48;
		write(1, &number, 1);
	}
}
