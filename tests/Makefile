CC = gcc
CFLAGS = -Wall -Werror -std=c99
LIBS = -lcheck -lm -lrt -lpthread -I ../includes

NAME = checker

SRC = 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $< 

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
    rm -f check_my_code check_my_code.o
