NAME = libsocket.a
LIBSO = $(NAME:%.a=%.so)
MAKE_DIR = .Makefiles
OBJ_DIR = .obj
CLIENT = client
SERVER = server
TEST = test
EXT = Makefile

.PHONY: clean fclean all re norme $(NAME) $(CLIENT) $(SERVER)

.SILENT:

all: $(NAME)

$(NAME): $(CLIENT) $(SERVER)

$(LIBSO): $(OBJ)

$(CLIENT):
	@make -f $(MAKE_DIR)/$(CLIENT).$(EXT)

$(SERVER):
	@make -f $(MAKE_DIR)/$(SERVER).$(EXT)

$(TEST): $(NAME)
	@make -f $(MAKE_DIR)/$(TEST).$(EXT)

clean:
	@make -f $(MAKE_DIR)/$(CLIENT).$(EXT) clean
	@make -f $(MAKE_DIR)/$(SERVER).$(EXT) clean

fclean:
	@make -f $(MAKE_DIR)/$(CLIENT).$(EXT) fclean
	@make -f $(MAKE_DIR)/$(SERVER).$(EXT) fclean
	@make -f $(MAKE_DIR)/$(TEST).$(EXT) fclean

norme:
	@make -f $(MAKE_DIR)/$(CLIENT).$(EXT) norme
	@make -f $(MAKE_DIR)/$(SERVER).$(EXT) norme

re:
	@make -f $(MAKE_DIR)/$(CLIENT).$(EXT) re
	@make -f $(MAKE_DIR)/$(SERVER).$(EXT) re
