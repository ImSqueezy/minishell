#include "../../Includes/parsing.h"

static char	*specials_expander(int *index, t_pdata *ptr)
{
	char	*value;

	value = ft_strdup("pidlater");
	*index += 1;
	return (value);
}

static int	is_specialparam(char c)
{
	return (c == '$' || c == '-' || c == '?');
}

char	*set_newstr(char *dst, char *src, int n)
{
	char	*tmp;

	tmp = dst;
	dst = ft_strnjoin(tmp, src, n);
	free(tmp);
	return (dst);
}

char	*getenv_value(const char *str, t_pdata *ptr, int *index)
{
	int		li;
	char	*key;
	char	*value;
	t_env	*curr;

	(1) && (li = 0, value = NULL);
	if (is_specialparam(str[li]))
		return (specials_expander(index, ptr));
	else if (str[li] == '\0')
		return (ft_strdup("$"));
	while (str[li] && (str[li] != ' ' && str[li] != '$'
			&& str[li] != '\'' && str[li] != '\"') && str[li] != '=')
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
