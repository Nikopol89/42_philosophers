NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Werror -Wextra
DEBUG = -g -fsanitize=address

SRCDIR = ./src
SRCFILES = main_bonus.c init_args_bonus.c utils_bonus.c routine_bonus.c
SRC = $(addprefix $(SRCDIR)/,$(SRCFILES))
OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -pthread -o $@ $^

clean:
	rm -f $(NAME) $(OBJ)

re: clean all

debug : $(OBJ)
	$(CC) $(CFLAGS) $(DEBUG) -pthread -o $(NAME) $^

redebug: clean debug