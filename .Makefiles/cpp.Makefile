# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    cpp.Makefile                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pribault <pribault@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/16 14:01:19 by pribault          #+#    #+#              #
#    Updated: 2018/04/16 14:01:46 by pribault         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libsocket.a
NAMESO = $(NAME:%.a=%.so)
CC = clang++
SRC =	socket_new.cpp
DIR = cpp
SRC_DIR = src
OBJ_DIR = .obj
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/$(DIR)/%.o)
FLAGS = -Wall -Wextra -Werror
INCLUDES =	libsocket.h
INCLUDE = $(INCLUDES:%.h=include/%.h)
N = 0
MAX = $(words $(OBJ))
COMPILED = false
PREFIX_NAME = libsocket_CPP

.PHONY: clean fclean all re norme

.SILENT:

all: $(NAME)
	@if [ $(COMPILED) = true ]; then echo "\033[0m\033[38;5;166m[$(PREFIX_NAME) ∎∎∎∎] \033[0m🐹  \033[38;5;214m$(NAME) done\033[0m"; else echo "\033[0m\033[38;5;166m[$(PREFIX_NAME) ∎∎∎∎] \033[0m🐹  \033[38;5;214mnothing to be done\033[0m"; fi

$(OBJ_DIR):
	@mkdir $@

$(OBJ_DIR)/$(DIR): | $(OBJ_DIR)
	@mkdir $@

$(OBJ_DIR)/$(DIR)/%.o: $(SRC_DIR)/$(DIR)/%.cpp $(INCLUDE) | $(OBJ_DIR)/$(DIR)
	@$(CC) $(FLAGS) -fPIC -I include -o $@ -c $<
	@$(eval N=$(shell echo $$(($(N)+1))))
	@$(eval PERCENT=$(shell echo $$((($(N)*100)/$(MAX)))))
	@printf "\033[0m\033[38;5;166m[$(PREFIX_NAME) \033[38;5;7m%3u%%\033[38;5;166m] \033[0m🌶  \033[38;5;226m$(@:$(OBJ_DIR)/$(DIR)/%.o=%.o) done\033[0m\n" $(PERCENT)

$(NAME): $(OBJ)
	@ar qc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@$(eval COMPILED=true)

clean:
	@rm -rf $(OBJ_DIR)/$(DIR)
	@echo "\033[0m\033[38;5;166m[$(PREFIX_NAME) ∎∎∎∎] \033[0m\033[38;5;45mobject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAMESO)
	@echo "\033[0m\033[38;5;166m[$(PREFIX_NAME) ∎∎∎∎] \033[0m\033[38;5;87m$(NAME) and $(NAMESO) removed\033[0m"

norme:
	@norminette $(OBJ:$(OBJ_DIR)/%.o=$(SRC_DIR)/%.c) $(INCLUDE)

re: fclean all
