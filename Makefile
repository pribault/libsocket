NAME = libsocket.a
LIBSO = $(NAME:%.a=%.so)
CC = clang
CLIENT_SRC = new_client.c
SERVER_SRC = new_server.c
SRC =	$(CLIENT_SRC:%.c=client/%.c)\
		$(SERVER_SRC:%.c=server/%.c)
OBJ = $(SRC:%.c=obj/%.o)
FLAGS = -Wall -Wextra
INCLUDES =	libsocket.h
INCLUDE = $(INCLUDES:%.h=include/%.h)
LIBFT = libft

.PHONY: clean fclean all re norme

all: $(NAME)

obj:
	@mkdir obj

obj/client: | obj
	@mkdir obj/client

obj/server: | obj
	@mkdir obj/server

obj/client/%.o: src/client/%.c $(INCLUDE) | obj/client
	@$(CC) $(FLAGS) -fPIC -I include -I $(LIBFT)/include -o $@ -c $<
	@echo "\033[0m🌶  \033[38;5;226m$@ done\033[0m"

obj/server/%.o: src/server/%.c $(INCLUDE) | obj/server
	@$(CC) $(FLAGS) -fPIC -I include -I $(LIBFT)/include -o $@ -c $<
	@echo "\033[0m🌶  \033[38;5;226m$@ done\033[0m"

$(LIBSO): $(OBJ)
	@$(CC) $(FLAGS) -shared -o $(LIBSO) $(OBJ)
	@echo "\033[0m🦁  \033[38;5;214m$@ done\033[0m"

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[0m🐹  \033[38;5;214m$@ done\033[0m"

clean:
	@rm -rf obj
	@echo "\033[0m\033[38;5;45mobject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBSO)
	@echo "\033[0m\033[38;5;87m$(NAME) and $(LIBSO) removed\033[0m"

norme:
	@norminette $(OBJ:%.o=%.c) $(INCLUDE)

re: fclean all
