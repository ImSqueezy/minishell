#ifndef EXECUTION_H
# define EXECUTION_H

# define INVALID_IDENTIFIER "minishell: export: `%s': not a valid identifier\n"

void	executer(t_gdata	*data);
int		echo(char **cmd);
int		env(t_env *head);
int		export(t_gdata *data);
int		check_symbols(char *identifier);
char	*append_value(char *old_value, char *to_append);
void	print_env(char **env);
int		unset(t_gdata *shell, char **ar);

#endif