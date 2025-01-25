#include "minitalk.h"

// void sender(int pid, char *message)
// {
//   printf("\n%s\n", message);
// 	kill(pid, SIGUSR1);
// 		usleep(42);
// }


int main(int ac, char **av)
{
  pid_t pid = atoi(av[1]); 
  printf("the process you'r trying to connect to is %d\n", pid);
  kill(pid, SIGUSR2);
  return (0);
}