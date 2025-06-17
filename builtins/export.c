<<<<<<< HEAD
#include "../execution.h"
=======
#include "../execution/execution.h"
>>>>>>> master

int is_valid_identifier(const char *arg)
{
    if (!arg || !(*arg))
        return 0;
    if (!(ft_isalpha(*arg) || *arg == '_'))
        return 0;
    for (int i = 1; arg[i] && arg[i] != '='; i++)
    {
        if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
            return 0;
    }
    return 1;
}

void update_or_add_env(t_env **env, const char *arg)
{
    t_env *current = *env;
    size_t name_len = strchr(arg, '=') ? strchr(arg, '=') - arg : strlen(arg);

    while (current)
    {
        if (strncmp(current->value, arg, name_len) == 0 && current->value[name_len] == '=')
        {
            free(current->value);
            current->value = strdup(arg);
            return;
        }
        current = current->next;
    }

    t_env *new = create_env_node(arg);
    if (!new) return;

    new->next = *env;
    *env = new;
}

void print_env_sorted(t_env *env)
{
    while (env)
    {
        printf("%s\n", env->value);
        env = env->next;
    }
}

void ft_export(char **args, t_env **env)
{
    if (!args[1])
    {
        print_env_sorted(*env);
        return;
    }

    for (int i = 1; args[i]; i++)
    {
        if (!is_valid_identifier(args[i]))
        {
            perror("export: not a valid identifier\n");
            continue;
        }
        update_or_add_env(env, args[i]);
    }
}





t_env *load_env_from_file()
{
    FILE *file = fopen(ENV_FILE, "r");
    if (!file) return NULL;

    char buffer[1024];
    t_env *env = NULL;
    t_env *tail = NULL;

    while (fgets(buffer, sizeof(buffer), file))
    {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = '\0';

        t_env *node = create_env_node(buffer);
        if (!node) continue;

        if (!env)
            env = node;
        else
            tail->next = node;

        tail = node;
    }

    fclose(file);
    return env;
}

int is_in_envp(const char *var, char **envp)
{
    size_t len = strchr(var, '=') ? strchr(var, '=') - var : strlen(var);
    for (int i = 0; envp[i]; i++)
    {
        if (strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
            return 1;
    }
    return 0;
}

void save_custom_env_to_file(char **envp, t_env *env)
{
    FILE *file = fopen("env_store.txt", "w");
    if (!file) return;

    while (env)
    {
        if (!is_in_envp(env->value, envp))
            fprintf(file, "%s\n", env->value);
        env = env->next;
    }

    fclose(file);
}

// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     t_env *env = NULL;
//     t_env *new_node = NULL;
//     t_env *tail = NULL;
//     int i = 0;

//     // Step 1: Convert envp[] into your t_env linked list
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

//     // Step 2: Load previously exported variables from file
//     t_env *saved_env = load_env_from_file();

//     // Step 3: Merge saved_env into env (but only if not already in envp)
//     t_env *current = saved_env;
//     while (current)
//     {
//         update_or_add_env(&env, current->value);
//         current = current->next;
//     }
//     free_env_list(saved_env); // free merged saved_env

//     // Step 4: Apply export from command-line args (argv[1..])
//     ft_export(argv, &env);

//     // Step 5: Save updated env to file (only custom variables)
//     save_custom_env_to_file(envp, env); // we'll write this helper

//     // Step 6: Print the resulting environment
//     print_env_sorted(env);

//     // Step 7: Clean up
//     free_env_list(env);
//     return 0;
// }

