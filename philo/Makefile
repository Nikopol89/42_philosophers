NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra
DEBUG = -g -fsanitize=thread

SRCDIR = ./src
SRCFILES = main.c init_args.c init_main.c routine_safe.c utils.c
SRC = $(addprefix $(SRCDIR)/,$(SRCFILES))
OBJ = ${SRC:.c=.o}

# THIS VERSION IS NOT DEADLOCK SAFE : DEMO ONLY FOR SIMULATION BENCHMARKS
SRCFILES_NS = main.c init_args.c init_main.c routine_unsafe.c utils.c
SRC_NS = $(addprefix $(SRCDIR)/,$(SRCFILES_NS))
OBJ_NS = ${SRC_NS:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -pthread -o $@ $^

clean:
	rm -f $(NAME) $(OBJ)

fclean:
	rm -f $(NAME) $(OBJ) $(OBJ_NS)

re: clean all

unsafe: $(OBJ_NS)
	$(CC) $(CFLAGS) -pthread -o $(NAME) $^

reunsafe: fclean unsafe

debug : $(OBJ)
	$(CC) $(CFLAGS) $(DEBUG) -pthread -o $(NAME) $^

redebug: fclean debug