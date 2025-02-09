#include "minitalk.h"


static void	handel(int sig, siginfo_t *siginfo, void *moreinfo)
{
	static unsigned char character ;
	static int pid;
	static int bit_number ;
	(void)moreinfo;
	if (pid == 0 || pid != siginfo->si_pid)
	{
		pid = siginfo->si_pid;
		bit_number = 0;
		character = 0;
	}
	if (sig == SIGUSR1)
	{
		character |=  (1 << bit_number);
	}
	bit_number++;
	if (bit_number == 8)
	{
		if (character == '\0')
			printf("\n");
		write(1, &character, 1);
		character = 0;
		bit_number = 0;
	}	
}


int main(void)
{
	printf("%d\n", getpid());
	struct sigaction sa;
	sa.sa_sigaction = &handel;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

