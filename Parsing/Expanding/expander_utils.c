#include "../../minishell.h"

char	*set_newstr(char *dst, char *src, int n)
{
	char	*tmp;

	tmp = dst;
	dst = ft_strnjoin(tmp, src, n);
	free(tmp);
	return (dst);
}

// $? must be handled
char	*getenv_value(t_pdata *ptr, const char *str, int *index)
{
	int		li;
	char	*key;
	char	*value;
	t_env	*curr;

	(1) && (li = 0, value = NULL);
	if (*(str - 1) == *str)
		return (ft_strdup(&*(str + 1)));
	while (str[li] && (ft_isalnum(str[li]) || str[li] == '_')) 
		li++;
	key = ft_strndup(str, li);
	curr = ptr->env;
	while (curr)
	{
		if (!ft_strcmp(key, curr->key))
		{
			value = ft_strdup(curr->value);
			break ;
		}
		curr = curr->next;
	}
	*index += li;
	return (free(key), value);
}

void	suppress_emptytokens(t_token **head)
{
	t_token	*curr;
	t_token	*next;

	curr = *head;
	while (curr)
	{
		next = curr->next;
		if (!ft_strcmp(curr->word, "") && curr->type != file)
			token_lstdelone(head, curr, del);
		curr = next;
	}
}
