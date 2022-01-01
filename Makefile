NAME = philosophers
CSRC = main.c
OBJ = $(CSRC:%.c=%.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $^

clean :
	rm -rf *.o

fclean : clean
	rm -rf $(NAME)

re : fclean all
