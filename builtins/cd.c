#include "../execution/execution.h"

void put_error(const char *msg)
{
    write(2, msg, strlen(msg));
}

int cd_command(int argc, char *argv[])
{
    if (argc != 2)
    {
        put_error("cd: usage: cd [path]\n");
        return (-1);
    }
    if (chdir(argv[1]) != 0)
    {
        put_error("cd: No such file or directory");
        put_error("\n");
        return (1);
    }
    return (0);
}


// int main(int argc, char *argv[])
// {
//     if (cd_command(argc, argv) == 0)
//     {
//         char cwd[1024];
//         if (getcwd(cwd, sizeof(cwd)) != NULL)
//         {
//             write(1, "Current directory: ", 19);
//             write(1, cwd, strlen(cwd));
//             write(1, "\n", 1);
//         }
//         else
//         {
//             put_error("cd: Failed to get current directory\n");
//         }
//     }

//     return (0);
// }
