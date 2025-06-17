#include "../execution/execution.h"

void try_exec_from_directories(char **dirs, t_cmd *cmd, char **envp)
{
    for (int i = 0; dirs[i]; i++)
    {
        char *full = ft_strjoin3(dirs[i], "/", cmd->first);
        if (!full)
            continue;

        if (access(full, X_OK) == 0)
        {
            execve(full, cmd->cmd, envp);
            perror("execve failed\n");
            free(full);
            clean_string_array(dirs);
            exit(1);
        }
        free(full);
    }
}

void search_and_exec_in_path(t_cmd *cmd, char **envp)
{
    char **dirs = get_path_directories();
    try_exec_from_directories(dirs, cmd, envp);
    perror("Command not found\n");
    clean_string_array(dirs);
    exit(127);
}

void execute_in_child(t_cmd *cmd, char **envp, int pipe_fd[2])
{
    handle_redirections(cmd, pipe_fd);
    if (check_builtin(cmd->first))
        exit(execute_builtin(cmd->cmd, cmd));
    if (try_exec_absolute_or_relative_path(cmd, envp))
        return;
    search_and_exec_in_path(cmd, envp);
}

void parent_process(t_cmd *cmd, pid_t pid, int pipe_fd[2])
{
    if (cmd->fd_out != 1)
    {
        close(pipe_fd[1]);
        cmd->fd_out = pipe_fd[0];
    }
    if (cmd->fd_out == 1)
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

void execute_command(t_cmd *cmd, char **envp)
{
    int pipe_fd[2];
    pid_t pid;

    if (!cmd)
        return;
    setup_pipes_and_fork(cmd, pipe_fd, &pid);
    if (pid == 0)
        execute_in_child(cmd, envp, pipe_fd);
    else if (pid > 0)
        parent_process(cmd, pid, pipe_fd);
    else
        perror("fork failed\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////










// void execute_command(t_cmd *cmd, char **envp)
// {
//     int pipe_fd[2];
//     pid_t pid;

//     if (!cmd)
//         return;

//     if (cmd->fd_out != 1)
//         pipe(pipe_fd);

//     pid = fork();
//     if (pid == 0)
//     {
//         if (cmd->fd_in != 0)
//         {
//             dup2(cmd->fd_in, 0);
//             close(cmd->fd_in);
//         }
//         if (cmd->fd_out != 1)
//         {
//             dup2(pipe_fd[1], 1);
//             close(pipe_fd[0]);
//             close(pipe_fd[1]);
//         }

//         if (check_builtin(cmd->first))
//             exit(execute_builtin(cmd->cmd, cmd));

//         // si cmd->first est un chemin absolu ou relatif
//         if (cmd->first[0] == '/' )
//         {
//             if (access(cmd->first, X_OK) == 0)
//                 execve(cmd->first, cmd->cmd, envp);
//             ft_puterr("Executable path is invalid\n");
//             exit(1);
//         }

//         // sinon, cherchons dans $PATH
//         char *path = get_path();
//         if (!path)
//         {
//             ft_puterr("PATH not found\n");
//             exit(1);
//         }

//         char **dirs = ft_split(path, ':');
//         if (!dirs)
//             exit(1);

//         for (int i = 0; dirs[i]; i++)
//         {
//             char *full = ft_strjoin3(dirs[i], "/", cmd->first);
//             if (!full)
//                 continue;

//             if (access(full, X_OK) == 0)
//             {
//                 execve(full, cmd->cmd, envp);
//                 ft_puterr("execve failed\n");
//                 free(full);
//                 clean_string_array(dirs);
//                 exit(1);
//             }
//             free(full);
//         }

//         ft_puterr("Command not found\n");
//         clean_string_array(dirs);
//         exit(127);
//     }
//     else if (pid > 0)
//     {
//         if (cmd->fd_out != 1)
//         {
//             close(pipe_fd[1]);
//             cmd->fd_out = pipe_fd[0];
//         }

//         if (cmd->fd_out == 1)
//         {
//             int status;
//             waitpid(pid, &status, 0);
//         }
//     }
//     else
//     {
//         ft_puterr("fork failed\n");
//     }
// }