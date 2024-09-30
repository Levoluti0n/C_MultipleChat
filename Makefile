NAME_CLIENT = client
NAME_SERVER = server
CC = gcc
CC_FLAGS = #-Wall -Wextra -Werror
LINKERS = -I includes/
SRC_CLIENT = $(wildcard utils/*.c) client.c
SRC_SERVER = $(wildcard utils/*.c) server.c
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
HEADERS = $(wildcard includes/*.h)

all: $(NAME_CLIENT)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CC_FLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT)

server: $(NAME_SERVER)

$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(CC_FLAGS) $(OBJ_SERVER) -o $(NAME_SERVER)

%.o: %.c $(HEADERS)
	$(CC) $(LINKERS) $(CC_FLAGS) -c $< -o $@

fclean: clean
	@rm -rf $(NAME_CLIENT) $(NAME_SERVER)

clean:
	@rm -rf $(OBJ_CLIENT) $(OBJ_SERVER)

re: fclean all
