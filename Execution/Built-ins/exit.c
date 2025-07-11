#include "../../minishell.h"

int	is_numeric(char *s)
{
	int	i;

	i = 0;
	if (!ft_strcmp(s, ""))
		return (0);
	if (s[0] == '+' || s[0] == '-')
		i++;
	while(s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return 0;
		i++;
	}
	return (1);
}

int	count_arr(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
		i++;
	return (i);
}


int	exit_builtin(char **cmd, int exit_st)
{
	int	i;
    int count;

	count = count_arr(cmd);
	i = 0;
	if (count == 1)
		exit(exit_st);
	else if (count > 1 && !is_numeric(cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2); // get back later (exit status d bash)
	}
	else if (count == 2)
	{
		exit(ft_atoi(cmd[1]));
	}
	else
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	return 0;
}
