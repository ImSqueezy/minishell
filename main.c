#include "Includes/parsing.h"

int    token_size(t_token *ptr);

int    parser(char *input, t_pdata *pdata)
{
    t_gdata    *gdata;
    char    *newinput;

    add_history(input);
    lexer(input, pdata, gdata); // processes input filles pdata if a parse error didn't occur
    expansions_search(pdata);
    token_lstclear(&pdata->token, del);
    return (1);
}

void    free_minishell(t_pdata *ptr)
{
    token_lstclear(&ptr->token, del);
    env_lstclear(&ptr->env, del);
}

int main(int ac , char **av, char **env)
{
    t_pdata pdata;
    char    *read;

    pdata.env = NULL;
    pdata.token = NULL;
    get_env(&pdata.env, env);
    while (1)
    {
        read = readline("$");
        if (!read)
            return (printf("minishell exited!\n"), free_minishell(&pdata), 0);
        parser(read, &pdata);
    }
    return (0);
}
