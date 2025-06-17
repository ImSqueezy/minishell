<<<<<<< HEAD
#include "../execution.h"
=======
#include "../execution/execution.h"
>>>>>>> master

int is_env_match(const char *str, const char *env_var)
{
    while (*env_var && *str && *str == *env_var)
    {
        str++;
        env_var++;
    }
    return (*str == '\0' && *env_var == '=');
}

void ft_unset(char **args, t_env **env)
{
    t_env *current = *env;
    t_env *previous = NULL;

    if (!args[1])
    {
        write(2, "unset: missing argument\n", 24);
        return ;
    }
    while (current)
    {
        if (is_env_match(args[1], current->value))
        {
            if (previous == NULL)
                *env = current->next;
            else
                previous->next = current->next;
            free(current->value);
            free(current);
            return ;
        }
        previous = current;
        current = current->next;
    }
    write(2, "unset: no such variable\n", 24);
}

// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;
//     t_env *env = NULL;
//     t_env *new_node = NULL;
//     t_env *tail = NULL;
//     int i = 0;

//     // Convert real envp into your t_env linked list
//     while (envp[i])
//     {
//         new_node = create_env_node(envp[i]);
//         if (!new_node)
//         {
//             free_env_list(env);
//             return 1;
//         }
//         if (!env)
//             env = new_node;
//         else
//             tail->next = new_node;
//         tail = new_node;
//         i++;
//     }

//     // Simulate: unset PATH (you can change this)
//     char *args[] = {"unset", "COLORTERM", NULL};

//     ft_unset(args, &env);

//     // Print result
//     t_env *current = env;
//     while (current)
//     {
//         printf("%s\n", current->value);
//         current = current->next;
//     }

//     free_env_list(env);
//     return 0;
// }

