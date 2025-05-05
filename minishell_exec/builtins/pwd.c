#include "builtins.h"


int pwd_command(void)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        ft_putstr_fd(cwd, 1);
        write(1, "\n", 1);
        return (0);
    }
    else
    {
        perror("ERROR ");
        return (1);
    }
}

// int main(void)
// {
//     return pwd_command();
// }
