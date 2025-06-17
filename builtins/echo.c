#include "../execution.h"


bool is_valid_n_option(const char *arg)
{
    int i;

    i = 2;
    if (arg[0] != '-' || arg[1] != 'n')
        return false;
    while (arg[i])
    {
        if (arg[i] != 'n')
            return false;
        i++;
    }
    return true;
}

void my_echo(int argc, char *argv[])
{
    int i;
    bool newline;

    i = 1;
    newline = true;

    while (i < argc && is_valid_n_option(argv[i]))
    {
        newline = false;
        i++;
    }
    while (i < argc)
    {
        ft_putstr_fd(argv[i], 1);
        if (i < argc - 1)
            ft_putstr_fd(" ", 1);
        i++;
    }

    if (newline)
        printf("\n");
}

// int main(int argc, char *argv[])
// {
//     my_echo(argc, argv);
//     return 0;
// }
