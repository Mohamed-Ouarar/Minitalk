/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarar <mouarar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:27:41 by mouarar           #+#    #+#             */
/*   Updated: 2025/02/23 18:10:18 by mouarar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handel(int sig, siginfo_t *siginfo, void *moreinfo)
{
	static int					bit_number;
	static int					pid;
	static unsigned char		character;

	(void)moreinfo;
	if (pid == 0 || pid != siginfo->si_pid)
	{
		pid = siginfo->si_pid;
		bit_number = 0;
		character = 0;
	}
	if (sig == SIGUSR1)
		character |= (1 << bit_number);
	bit_number++;
	if (bit_number == 8)
	{
		if (character == '\0')
			write(1, "\n", 1);
		write(1, &character, 1);
		character = 0;
		bit_number = 0;
	}
}

static void	print_pid(unsigned long long num)
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

int	main(void)
{
	struct sigaction	sa;

	print_pid(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = &handel;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
