#include "../execution/execution.h"
#include "../libft/libft.h"

t_env *create_env_node(const char *str)
{
    t_env *node = malloc(sizeof(t_env));
    if (!node)
        return NULL;
    node->value = ft_strdup(str);
    node->next = NULL;
    return node;
}

void free_env_list(t_env *env)
{
    t_env *tmp;
    while (env)
    {
        tmp = env;
        env = env->next;
        free(tmp->value);
        free(tmp);
    }
}

int	ft_isdigit(int c)
{
	unsigned char	ch;

	if (c < 0 || c > 255)
		return (0);
	ch = (unsigned char)c;
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	unsigned char	ch;

	if (c < 0 || c > 255)
		return (0);
	ch = (unsigned char)c;
	if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	unsigned char	ch;

	if (c < 0 || c > 255)
		return (0);
	ch = (unsigned char)c;
	if (ft_isalpha(ch) || ft_isdigit(ch))
		return (1);
	return (0);
}



