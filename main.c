#include "Includes/parsing.h"

int    token_size(t_token *ptr);

char    *ft_strndup(const char *s1, int n)
{
    int        i;
    char    *new;

    new = malloc(sizeof(char) * n + 1);
    if (!new)
        return (NULL);
    i = ft_strleapy(new, s1, n + 1);
    return (new);
}

int    ft_strcmp(const char *s1, const char *s2)
{
    int    i;

    i = 0;
    while (s1[i] && s2[i] && (s1[i] == s2[i]))
        i++;
    return (s1[i] - s2[i]);
}

char    *getenv_value(const char *str, t_env *env, int *index)
{
    int            li;
    char    *key;
    char    *value;
    t_env        *curr;

    value = NULL;
    li = 0;
	if (!str[li])
		return (ft_strdup("$"));
    while (str[li] && (str[li] != '$' && str[li] != '\'' && str[li] != '\"'))
        li++;
    key = ft_strndup(str, li);
    curr = env;
    while (curr)
    {
        int var = ft_strcmp(key ,curr->key);
        if (!var)
        {
            value = ft_strdup(curr->value);
            break ;
        }
        curr = curr->next;
    }
    *index += li;
    return (value);
}

char    *ft_strnjoin(const char *s1, const char *s2, int n);

char    *expand(char *word, int *quoting, t_env *env)
{
    int        i;
    int        initial_len;
    char    *after_dollar, *newstr;

    newstr = NULL;
    initial_len = ft_strlen(word);
    i = 0;
    while (word[i])
    {
        if (word[i] == '$')
        {
            i++;
            after_dollar = getenv_value(&word[i], env, &i);
            newstr = ft_strjoin(newstr, after_dollar);
			i--;
        }
        else
		{
            newstr = ft_strnjoin(newstr, &word[i], 1);
		}
        i++;
    }
    free(word);
	printf("newstr: %s\n", newstr);
    return (newstr);
}

int    env_size(t_env *env)
{
    int    i = 0;
    while (env)
    {
        i++;
        env = env->next;
    }
    return (i);
}

void    expansions_search(t_pdata *ptr)
{
    t_token *curr;
    char    *new;
    int        old_tokensize;

    old_tokensize = token_size(ptr->token);
    curr = ptr->token;
    while (curr)
    {
        if (curr->var == 1)
            curr->word = expand(curr->word, &curr->quoting, ptr->env);
        curr = curr->next;
    }
    // if the list has a new size, it means that new tokes are added
    // variable expantion has occured
    if (token_size(ptr->token) != old_tokensize)
        expansions_search(ptr);
}

int    parser(char *input, t_pdata *pdata)
{
    t_gdata    *gdata;
    char    *newinput;

    add_history(input);
    lexer(input, pdata, gdata); // processes input filles pdata if a parse error didn't occur
    expansions_search(pdata);
    return (1);
}

int main(int ac , char **av, char **env)
{
    t_pdata pdata;
    char    *read;

    get_env(&pdata.env, env);
    while (1)
    {
        read = readline("$");
        if (!read)
            return (0);
        parser(read, &pdata);
    }
    return (0);
}

int    token_size(t_token *ptr)
{
    int    i;

    i = 0;
    while (ptr)
    {
        i++;
        ptr = ptr->next;
    }
    return (i);
}

char    *ft_strnjoin(const char *s1, const char *s2, int n)
{
    char    *new;
    size_t        j;
    size_t        i;
    size_t        size;

	// printf("s1 %s its size = %zu\n", s1, size);
	// printf("s2 %s\n", s2);
	if (!s1)
        return (ft_strndup(s2, n));
    else if (!s2)
        return (ft_strndup(s1, n));
    size = ft_strlen(s1) + n + 1;
    new = malloc(size * sizeof(char));
    if (!new)
        return (NULL);
    i = 0;
    j = 0;
    while (s1[i])
        new[j++] = s1[i++];
    i = ft_strlcat(new, s2, size);
	printf("new: %s\n", new);
    return (new);
}
