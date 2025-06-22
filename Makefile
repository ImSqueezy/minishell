# relink must be handled
# compilation must be done with the flags (Werror, Wextra and Wall)
# -g must be removed

NAME = minishell

LIBFT_OBJS = $(addprefix Libraries/Libft/, ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_strlen.o ft_memset.o ft_bzero.o \
ft_memcpy.o ft_memmove.o ft_strlcpy.o ft_strlcat.o ft_toupper.o ft_tolower.o ft_strchr.o ft_strrchr.o ft_strncmp.o \
ft_memchr.o ft_memcmp.o ft_strnstr.o ft_atoi.o ft_strdup.o ft_calloc.o ft_substr.o ft_substr.o ft_strjoin.o ft_strtrim.o \
ft_split.o ft_itoa.o ft_strmapi.o ft_striteri.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o)

LIBFT_PREFIX = Libraries/Libft/
LIBFT = Libraries/Libft/libft.a

FS = -fsanitize=address
# -g to be removed later
FLAGS = $(FS) -g # -Wall -Wextra -Werror
COMPILE = cc $(FLAGS) -c $< -o $@

EXPANDER_OBJS = $(addprefix Expanding/, expander.o utils.o qremoval.o expander_utils.o)
LEXER_OBJS = $(addprefix Lexer/, lexer.o dlst.o straddlen.o spacing.o tokenizer.o)
PARSING_OBJS = $(addprefix Parsing/, $(LEXER_OBJS) $(EXPANDER_OBJS) mem_related.o parser.o env.o)
OBJS = $(PARSING_OBJS) \
	main.o

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) Includes/parsing.h
	cc $(FS) -g $(OBJS) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT): $(LIBFT_OBJS)
	make -C $(LIBFT_PREFIX)

%.o: %.c
	$(COMPILE)

clean:
	rm -f $(OBJS) $(LIBFT_OBJS)

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
