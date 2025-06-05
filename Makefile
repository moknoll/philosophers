NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = src/main.c src/utils.c src/init.c src/routine.c src/philo.c src/monitor.c src/routine_forks.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
