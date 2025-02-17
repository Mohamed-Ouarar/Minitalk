/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarar <mouarar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:02:53 by mouarar           #+#    #+#             */
/*   Updated: 2025/02/16 17:19:19 by mouarar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

long	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	if (str[i] && !(str[i] >= '0' && str[i] <= '9'))
		return (-1);
	return (result);
}

void	send_char(char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(400);
	}
}

void	message_received(int sig)
{
	if (sig == SIGUSR1)
		write(1, "message received\n", 17);
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
	send_char('\n', pid);
	signal(SIGUSR1, message_received);
	send_char('\0', pid);
	return (0);
}
