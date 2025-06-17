#ifndef EXECUTION_H
#define EXECUTION_H
#define ENV_FILE "env_store.txt"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>



typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_cmd {
    char *first; 
    char **cmd;    
    int fd_in;       
    int fd_out;
    t_env *env;
} t_cmd;


char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int check_builtin(char *cmd);
int	execute_builtin(char **args, t_cmd *cmd);
int    ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *str);

//utils builtins
t_env *create_env_node(const char *str);
void free_env_list(t_env *env);
size_t	ft_strlen(const char *str);
int	ft_isalpha(int c);
int	ft_isalnum(int c);
int	ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);

//builtins commands
int cd_command(int argc, char *argv[]);
void my_echo(int argc, char *argv[]);
void    ft_env(t_env *env);
int pwd_command(void);
int ft_exit(char **args);
void ft_export(char **args, t_env **env);
void ft_unset(char **args, t_env **env);


void execute_command(t_cmd *cmd, char **envp);

char *get_path();
char *ft_strjoin3(char *s1, char *s2, char *s3);
void clean_string_array(char **arr);
void handle_redirections(t_cmd *cmd, int pipe_fd[2]); 
void setup_pipes_and_fork(t_cmd *cmd, int pipe_fd[2], pid_t *pid);
int try_exec_absolute_or_relative_path(t_cmd *cmd, char **envp);
char **get_path_directories();

#endif