/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarar <mouarar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:15:14 by mouarar           #+#    #+#             */
/*   Updated: 2025/02/24 10:31:26 by mouarar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static long	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (*str == '\0')
		return (-1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		if (result > 2147483647)
			return (-1);
		i++;
	}
	if (str[i] && !(str[i] >= '0' && str[i] <= '9'))
		return (-1);
	return (result);
}

static	void	send_char(char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
		{
			if (kill(pid, SIGUSR1) < 0)
			{
				write(2, "Failed to send signal!\n", 23);
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) < 0)
			{
				write(2, "Failed to send signal!\n", 23);
				exit(1);
			}
		}
		i++;
		usleep(200);
		usleep(200);
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;

	i = 0;
	if (ac != 3 || av[1][0] == '\0' || av[2][0] == '\0')
	{
		write(2, "Usage:./program <PID> <message>\n", 32);
		return (1);
	}
	pid = ft_atoi(av[1]);
	if (pid == -1)
	{
		write(2, "please enter a valid PID\n", 25);
		return (1);
	}
	while (av[2][i])
		send_char(av[2][i++], pid);
	send_char('\0', pid);
	return (0);
}
