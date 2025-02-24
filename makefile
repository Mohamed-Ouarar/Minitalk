SRC_SERVER = mandatory/server.c 
SRC_CLIENT = mandatory/client.c
OBJS_SERVER = $(SRC_SERVER:.c=.o)
OBJS_CLIENT = $(SRC_CLIENT:.c=.o)

BONUS_SRC_SERVER = bonus/server_bonus.c  bonus/minitalk_server_utlis_bonus.c
BONUS_SRC_CLIENT = bonus/client_bonus.c
BONUS_OBJS_SERVER = $(BONUS_SRC_SERVER:.c=.o)
BONUS_OBJS_CLIENT = $(BONUS_SRC_CLIENT:.c=.o)

BONUS_NAME = server_bonus client_bonus
NAME = server client

CC = cc
CFLAGS = -Wall -Wextra -Werror 

all : $(NAME)

server : $(OBJS_SERVER)
	$(CC) $^ -o server

client : $(OBJS_CLIENT)
	$(CC) $^ -o client

bonus : $(BONUS_NAME)

server_bonus : $(BONUS_OBJS_SERVER)
	$(CC) $^ -o server_bonus

client_bonus : $(BONUS_OBJS_CLIENT)
	$(CC) $^ -o client_bonus

$(OBJS_SERVER) $(OBJS_CLIENT): %.o : %.c mandatory/minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJS_SERVER) $(BONUS_OBJS_CLIENT) : %_bonus.o : %_bonus.c bonus/minitalk_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

fclean : clean
	rm -f $(NAME) $(BONUS_NAME)

clean : 
	rm -f $(OBJS_SERVER) $(BONUS_OBJS_SERVER) $(OBJS_CLIENT) $(BONUS_OBJS_CLIENT)

re : fclean all
