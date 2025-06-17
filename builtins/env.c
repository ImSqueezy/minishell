<<<<<<< HEAD
#include "../execution.h"
=======
#include "../execution/execution.h"
>>>>>>> master


int contains_equal(const char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

void    ft_env(t_env *env)
{
    while (env)
    {
        if (env->value && contains_equal(env->value))
        {
            write(1, env->value, ft_strlen(env->value));
            write(1, "\n", 1);
        }
        env = env->next;
    }
}

// int main(int argc, char **argv, char **env)
// {
//     t_env *head = NULL;
//     t_env *new_node;
//     t_env *ev;
//     int i = 0;

//     (void)argc;
//     (void)argv;

//     while (env[i])
//     {
//         new_node = create_env_node(env[i]);
//         if (!new_node)
//         {
//             free_env_list(head);
//             return (1);
//         }
//         if (!head)
//             head = new_node;
//         else
//             ev->next = new_node;
//         ev = new_node;
//         i++;
//     }

//     ft_env(head);         // print environment variables
//     free_env_list(head);  // clean up
//     return 0;
// }
