#ifndef EXECUTION_H
#define EXECUTION_H
#define ENV_FILE "env_store.txt"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>


typedef struct s_env{
    char            *value;
    struct s_env    *next;
}                   t_env;


void	ft_putstr_fd(char *s, int fd);
t_env *create_env_node(const char *str);
void free_env_list(t_env *env);
size_t	ft_strlen(const char *str);
int	ft_isalpha(int c);
int	ft_isalnum(int c);
int	ft_isdigit(int c);

#endif