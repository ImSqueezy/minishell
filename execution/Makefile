FILES = ../builtins/cd.c \
		../builtins/echo.c \
		../builtins/env.c \
		../builtins/exit.c \
		../builtins/export.c \
		../builtins/pwd.c \
		../builtins/unset.c \
		../builtins/utils.c \
		builtins_check.c \
		test1.c \
		utils.c \
		utils1.c \
		utils2.c \
		main.c \
		utils3.c

OBJS = ${FILES:%.c=%.o}
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = execute

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c execution.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
