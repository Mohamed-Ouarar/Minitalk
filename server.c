#include "minitalk.h"


void handel(int signale)
{
	printf("\n%d\n",signale);
}


int main(void)
{
	printf("%d\n", getpid());
	signal(SIGUSR1, handel);
	signal(SIGUSR2, handel);
	while (1)
		pause();
	return (0);
}