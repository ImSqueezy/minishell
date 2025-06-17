#include "../execution/execution.h"

int is_numeric(const char *str)
{
    int i = 0;

    if (!str || !str[0])
        return 0;
    if (str[0] == '-' || str[0] == '+')
        i++;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

int	ft_atoi(const char *str)
{
	int		s;
	long	r;
	int		i;

	s = 1;
	r = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= (-1);
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (s == 1 && r > (LONG_MAX / 10))
			return (-1);
		else if (s == -1 && r > LONG_MAX / 10)
			return (0);
		r = r * 10 + str[i] - '0';
		i++;
	}
	return (s * r);
}

int ft_exit(char **args)
{
    long code;

    printf("exit\n");
    if (!args)
        exit(0);
    if (args[1])
    {
        if (!is_numeric(args[1]))
        {
            write(2, "exit: numeric argument required\n", 32);
            exit(255);
        }
        if (args[2])
        {
            write(2, "minishell: exit: too many arguments\n", 36);
            return 1;
        }
        code = ft_atoi(args[1]);
        exit((unsigned char)code);
    }
    exit(0);
}
// int main(int argc, char **argv)
// {
//     (void)argc;
//     ft_exit(argv);
//     return 0;
// }
