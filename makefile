SRC_SERVER = server.c 
SRC_CLIENT = client.c
OBJS_SERVER = $(SRC_SERVER:.c=.o)
OBJS_CLIENT = $(SRC_CLIENT:.c=.o)

BONUS_SRC_SERVER = server_bonus.c  minitalk_server_utlis_bonus.c
BONUS_SRC_CLIENT = client_bonus.c
BONUS_OBJS_SERVER = $(BONUS_SRC_SERVER:.c=.o)
BONUS_OBJS_CLIENT = $(BONUS_SRC_CLIENT:.c=.o)

BONUS_NAME = server_bonus client_bonus
NAME = server client

CC = cc
CFLAGS = -Wall -Wextra -Werror 

all : $(NAME)

server : $(OBJS_SERVER)
	$(CC) -fsanitize=address $^ -o server

client : $(OBJS_CLIENT)
	$(CC) -fsanitize=address $^ -o client

bonus : $(BONUS_NAME)

server_bonus : $(BONUS_OBJS_SERVER)
	$(CC) -fsanitize=address $^ -o server_bonus

client_bonus : $(BONUS_OBJS_CLIENT)
	$(CC) -fsanitize=address $^ -o client_bonus

$(OBJS_SERVER) $(OBJS_CLIENT): %.o : %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJS_SERVER) $(BONUS_OBJS_CLIENT) : %_bonus.o : %_bonus.c minitalk_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

fclean : clean
	rm -f $(NAME) $(BONUS_NAME)

clean : 
	rm -f $(OBJS_SERVER) $(BONUS_OBJS_SERVER) $(OBJS_CLIENT) $(BONUS_OBJS_CLIENT)

re : fclean all
