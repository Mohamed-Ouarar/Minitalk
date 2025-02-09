SRC = server.c client.c
OBJS = $(SRC:.c=.o)
NAME = server client
CC = CC
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

server : server.o
	$(CC) server.o -o server

client : client.o
	$(CC) client.o -o client

%.o : %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

fclean : clean
	rm -f $(NAME)
clean : 
	rm -f $(OBJS)

re : fclean all