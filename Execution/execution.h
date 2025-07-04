#ifndef EXECUTION_H
# define EXECUTION_H

void	executer(t_gdata	*data);
int		echo(char **cmd);
int		env(t_env *head);
int		export(t_gdata *data);

#endif