NAME = minishell

LIBFT_OBJS = $(addprefix Libft/, ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_strlen.o ft_memset.o ft_bzero.o \
ft_memcpy.o ft_memmove.o ft_strlcpy.o ft_strlcat.o ft_toupper.o ft_tolower.o ft_strchr.o ft_strrchr.o ft_strncmp.o \
ft_memchr.o ft_memcmp.o ft_strnstr.o ft_atoi.o ft_strdup.o ft_calloc.o ft_substr.o ft_substr.o ft_strjoin.o ft_strtrim.o \
ft_split.o ft_itoa.o ft_strmapi.o ft_striteri.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o)

LIBFT_PREFIX = Libft/
LIBFT = Libft/libft.a

FLAGS = -Wall -Wextra -Werror
R_COMPILE = -I$(shell brew --prefix readline)/include
R_RELINK = -lreadline -L$(shell brew --prefix readline)/lib
COMPILE = cc -g $(FLAGS) $(R_COMPILE) -c $< -o $@

BUILTINS_OBJS = $(addprefix Built-ins/, echo.o exit.o export.o export_utils.o env.o unset.o cd.o pwd.o utils.o)
EXECUTION_OBJS = $(addprefix Execution/, $(BUILTINS_OBJS) executer.o ft_execution_split.o command_loop.o env_array.o \
	execute.o path_utils.o pipeline.o redirections.o utils.o)
EXPANDER_OBJS = $(addprefix Expanding/, expander.o utils.o qremoval.o expander_utils.o export.o export_utils.o)
LEXER_OBJS = $(addprefix Lexer/, lexer.o dlst.o straddlen.o spacing.o tokenizer.o)
DATA_F_OBJS = $(addprefix Data_fill/, env.o data_fill.o env_mem.o cmd_mem.o)
PARSING_OBJS = $(addprefix Parsing/, $(LEXER_OBJS) $(EXPANDER_OBJS) $(DATA_F_OBJS) heredoc.o heredoc_utils.o parser.o)
OBJS = $(PARSING_OBJS) $(EXECUTION_OBJS) \
	main.o utils.o

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cc -g $(OBJS) $(LIBFT) -o $(NAME) $(R_RELINK) 

$(LIBFT): $(LIBFT_OBJS)
	make -C $(LIBFT_PREFIX)

%.o: %.c Parsing/parsing.h Execution/execution.h minishell.h Libft/libft.h
	$(COMPILE)

clean:
	rm -f $(OBJS) $(LIBFT_OBJS)

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
