/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarar <mouarar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:59:27 by mouarar           #+#    #+#             */
/*   Updated: 2025/02/23 17:36:45 by mouarar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	printer(int *bit_number, unsigned char *c, int *client_pid, int *i)
{
	static int	size;
	static char	str[8];

	if (*bit_number == 8)
	{
		if (*i == 0)
			size = character_size(*c);
		str[(*i)++] = *c;
		if (*c == '\0')
			kill(*client_pid, SIGUSR1);
		if (--size == 0)
		{
			str[*i] = '\0';
			ft_putstr(str);
			*i = 0;
		}
		*c = 0;
		*bit_number = 0;
	}
}

static void	handel(int sig, siginfo_t *siginfo, void *moreinfo)
{
	static int					bit_number;
	static int					pid;
	static int					i;
	static unsigned char		character;

	(void)moreinfo;
	if (pid == 0 || pid != siginfo->si_pid)
	{
		pid = siginfo->si_pid;
		bit_number = 0;
		character = 0;
		i = 0;
	}
	if (sig == SIGUSR1)
		character |= (1 << bit_number);
	bit_number++;
	printer(&bit_number, &character, &pid, &i);
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
