# relink must be handled
# compilation must be done with the flags (Werror, Wextra and Wall)
# -g must be removed

NAME = minishell

LIBFT_OBJS = $(addprefix Libraries/Libft/, ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_strlen.o ft_memset.o ft_bzero.o \
ft_memcpy.o ft_memmove.o ft_strlcpy.o ft_strlcat.o ft_toupper.o ft_tolower.o ft_strchr.o ft_strrchr.o ft_strncmp.o \
ft_memchr.o ft_memcmp.o ft_strnstr.o ft_atoi.o ft_strdup.o ft_calloc.o ft_substr.o ft_substr.o ft_strjoin.o ft_strtrim.o \
ft_split.o ft_itoa.o ft_strmapi.o ft_striteri.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o)

COMPILE = cc -g -c $< -o $@
LIBFT_PREFIX = Libraries/Libft/
LIBFT = Libraries/Libft/libft.a
OBJS = $(PARSING_OBJS) \
	main.o Parsing/space.o
PARSING_OBJS = $(addprefix Parsing/, )

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cc -g $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C Libraries/Libft/

%.o: %.c
	$(COMPILE)

clean:
	rm -f $(OBJS) $(LIBFT_OBJS)

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: clean all