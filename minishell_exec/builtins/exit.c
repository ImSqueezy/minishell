#include "builtins.h"

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

long ft_atol(const char *str)
{
    int i = 0;
    long result = 0;
    int sign = 1;

    if (str[0] == '-' || str[0] == '+')
    {
        if (str[0] == '-')
            sign = -1;
        i++;
    }
    while (str[i])
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return sign * result;
}

int is_too_long(const char *str)
{
    char *max = "9223372036854775807";
    char *min = "9223372036854775808";
    int i = 0;

    int is_neg = (str[0] == '-');
    if (str[0] == '-' || str[0] == '+')
        str++;
    while (*str == '0')
        str++;
    int len = 0;
    while (str[len])
        len++;
    if (len > 19)
        return 1;
    if (len < 19)
        return 0;
    while (str[i])
    {
        if (str[i] > (is_neg ? min[i] : max[i]))
            return 1;
        else if (str[i] < (is_neg ? min[i] : max[i]))
            return 0;
        i++;
    }
    return 0;
}

void check_long_max(const char *str)
{
    if (is_too_long(str))
    {
        write(2, "exit: ", 6);
        write(2, str, strlen(str));
        write(2, ": numeric argument required\n", 29);
        exit(255);
    }
}

int ft_exit(char **args)
{
    long code;
    int in_pipeline = isatty(STDIN_FILENO);

    if (in_pipeline)
        write(2, "exit\n", 5);
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
        check_long_max(args[1]);
        code = ft_atol(args[1]);
        exit((unsigned char)code);
    }
    exit(0);
}
int main(int argc, char **argv)
{
    (void)argc;
    ft_exit(argv);
    return 0;
}
