CC = clang
FLAGS = -Wall -Wextra -Ofast
SRC = basic_server.c
BIN = $(SRC:%.c=.bin/%.out)
LIBFT = libft

.PHONY: fclean re

all: $(BIN)

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

%.out: %.c $(LIBFT)/libft.a
	@$(CC) $(FLAGS) -o $@ $< -I include -I $(LIBFT)/include -lsocket -L $(LIBFT) -lft 

fclean:
	@rm -f $(BIN)
	@if [ -a $(LIBFT)/libft.a ]; then make -C $(LIBFT) fclean; fi;

re: fclean all
