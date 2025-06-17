#include "execution.h"

void setup_pipes_and_fork(t_cmd *cmd, int pipe_fd[2], pid_t *pid)
{
    if (cmd->fd_out != 1)
        pipe(pipe_fd);

    *pid = fork();
}

void handle_redirections(t_cmd *cmd, int pipe_fd[2])
{
    if (cmd->fd_in != 0)
    {
        dup2(cmd->fd_in, 0);
        close(cmd->fd_in);
    }
    if (cmd->fd_out != 1)
    {
        dup2(pipe_fd[1], 1);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    }
}

int try_exec_absolute_or_relative_path(t_cmd *cmd, char **envp)
{
    if (cmd->first[0] == '/')
    {
        if (access(cmd->first, X_OK) == 0)
        {
            execve(cmd->first, cmd->cmd, envp);
            perror("execve failed\n");
            exit(1);
        }
        perror("Executable path is invalid\n");
        exit(1);
    }
    return 0;
}

char **get_path_directories()
{
    char *path = get_path();
    if (!path)
    {
        perror("PATH not found\n");
        exit(1);
    }

    char **dirs = ft_split(path, ':');
    if (!dirs)
        exit(1);

    return dirs;
}
