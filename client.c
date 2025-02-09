#include "minitalk.h"




long ft_atoi(char *str)
{
  int i = 0;
  long result = 0;
  while (str[i] && str[i] >= '0' && str[i] <= '9')
  {
      result = result * 10 + str[i] - 48;
      i++;
  }
  if (str[i] && !(str[i] >= '0' && str[i] <= '9'))
    return -1;
  return result;
}





void send_char(char c, int pid)
{
  int i = 0;
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


int main(int ac, char **av)
{
  int i = 0;
  int pid = ft_atoi(av[1]);
  if (pid == -1)
  {
    write(2, "please enter a valid PID\n", 25);
    return (1);
  }
  if (ac != 3 || av[1][0] == '\0' || av[2][0] == '\0')
  {
      write(2, "Usage:./program <PID> <message>\n", 32);
      return (1);
  } 
  while (av[2][i])
    send_char(av[2][i++], pid);
  send_char('\0', pid);
  return (0);
}