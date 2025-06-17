
#include "execution.h"

int check_builtin(char *cmd)
{
    if (!cmd)
        return 0;
    return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || 
            !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") ||
            !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") ||
            !ft_strcmp(cmd, "exit"));
}


int execute_builtin(char **args, t_cmd *cmd)
{
    int argc = 0;
    int result = 0;

    if (!args || !args[0])
        return 1;
    while (args[argc])
        argc++;
    if (ft_strcmp(args[0], "echo") == 0)
        my_echo(argc, args);
    else if (ft_strcmp(args[0], "cd") == 0)
        result = cd_command(argc, args);
    else if (ft_strcmp(args[0], "pwd") == 0)
        result = pwd_command();
    else if (ft_strcmp(args[0], "exit") == 0)
        result = ft_exit(args);
    else if (ft_strcmp(args[0], "env") == 0)
        ft_env(cmd->env);
    else if (ft_strcmp(args[0], "export") == 0)
        ft_export(args, &(cmd->env));
    else if (ft_strcmp(args[0], "unset") == 0)
        ft_unset(args, &(cmd->env));
    else
        return 0;
    return result;
}
