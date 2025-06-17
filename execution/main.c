
#include "execution.h" // contient la struct t_cmd + prototype execute_command

// void f()
// {
//     system("lsof -c execute");
// }

int main(int argc, char **argv, char **envp)
{
    t_cmd cmd;
    // atexit (f);
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        return 1;
    }

    // Remplir la structure
    cmd.cmd = &argv[1];           // ex: ./execute ls -l → cmd.cmd = ["ls", "-l", NULL]
    cmd.first = argv[1];          // le nom de la commande (ex: "ls")
    cmd.fd_in = STDIN_FILENO;
    cmd.fd_out = STDOUT_FILENO;
    cmd.env = NULL;               // adapte selon ton projet

    execute_command(&cmd, envp);

    return 0;
}
