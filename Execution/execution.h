#ifndef EXECUTION_H
# define EXECUTION_H

void	executer(t_gdata	*data);
int		echo(char **cmd);
int		env(t_env *head);
int		export(t_gdata *data);
int		check_symbols(char *identifier);
char	*append_value(char *old_value, char *to_append);
void	print_env(char **env);

#endif