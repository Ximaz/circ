SRC=main.c
CFLAGS=-Wall -Wextra -Werror -pedantic
NAME=a.out
LIBS=./circ/*.c

$(NAME):
	gcc -o $(NAME) $(SRC) $(LIBS) $(CFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re