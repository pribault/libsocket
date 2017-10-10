NAME = libsocket.a
CC = gcc
FLAGS = -Wall -Wextra -Ofast -fPIC
SRC =	client/new.c client/destroy.c\
		client/start.c client/stop.c\
		client/receive.c client/send.c\
		client/set_refresh_rate.c\
		client/set_timeout.c\
		client/start_autocleaner.c\
		client/stop_autocleaner.c\
		server/new.c server/destroy.c\
		server/start.c server/stop.c\
		server/receive.c server/send.c\
		server/set_refresh_rate.c\
		server/set_timeout.c\
		server/start_autocleaner.c\
		server/stop_autocleaner.c
INCLUDES =	libsocket.h
INCLUDE = $(INCLUDES:%.h=include/%.h)
OBJ = $(SRC:%.c=src/%.o)
LIBFT = libft

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c $(INCLUDE)
	@echo "\033[3m\033[38;5;87mcompiling $@\033[0m"
	@$(CC) $(FLAGS) -I include -I $(LIBFT)/include -o $@ -c $<

$(NAME): $(OBJ)
	@echo "\033[4m\033[1m\033[38;5;23mcompiling $(NAME)\033[0m"
	@ar rc $(NAME) $(OBJ)

clean:
	@echo "\033[3m\033[38;5;46mremoving object files\033[0m"
	@rm -f $(OBJ)

fclean: clean
	@echo "\033[1m\033[38;5;22mremoving $(NAME)\033[0m"
	@rm -f $(NAME)

re: fclean all

norme:
	@norminette $(OBJ:%.o=%.c) $(INCLUDE)
