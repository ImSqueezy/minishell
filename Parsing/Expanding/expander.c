/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:01:37 by aouaalla          #+#    #+#             */
/*   Updated: 2025/05/21 22:01:39 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parsing.h"

static void	squoting_traffic(int *flag)
{
	if (*flag == 0)
		*flag = 1;
	else
		*flag = 0;
}

static char	*getenv_value(const char *str, t_env *env, int *index)
{
	int		li;
	char	*key;
	char	*value;
	t_env	*curr;

	value = NULL;
	li = 0;
	if (!str[li])
		return (ft_strdup("$"));
	while (str[li] && (str[li] != ' ' && str[li] != '$' && str[li] != '\'' && str[li] != '\"'))
		li++;
	key = ft_strndup(str, li);
	curr = env;
	while (curr)
	{
		if (!ft_strcmp(key ,curr->key))
		{
			value = ft_strdup(curr->value);
			break ;
		}
		curr = curr->next;
	}
	*index += li;
	return (free(key), value);
}

char	*set_newstr(char *dst, char *src, int n)
{
	char *tmp = dst;

	dst = ft_strnjoin(tmp, src, n);
	free(tmp);
	return (dst);
}

static char    *expand(char *word, int *quoting, t_env *env)
{
	int		i;
	char	*after_dollar;
	char	*newstr;

	newstr = NULL;
	i = 0;
	while (word[i])
	{
		if (word[i] == '\'')
			squoting_traffic(quoting);
		if (word[i] == '$' && *quoting)
		{
			i++;
			after_dollar = getenv_value(&word[i], env, &i);
			if (after_dollar)
				newstr = set_newstr(newstr, after_dollar, ft_strlen(after_dollar));
			free(after_dollar);
			i--;
		}
		else
			newstr = set_newstr(newstr, &word[i], 1);
		i++;
	}
	return (free(word), newstr);
}

t_token	*token_addnew(char *word, int type, int quoting, int var)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->word = word;
	new_node->type = type;
	new_node->quoting = quoting;
	new_node->var = var;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void token_insert_after(t_token *current, t_token *new_node)
{
    if (!current || !new_node)
        return;
    new_node->prev = current;
    new_node->next = current->next;
    if (current->next)
        current->next->prev = new_node;
    current->next = new_node;
}

t_token	*subtokenizer(t_token **head, t_token *curr)
{
	char	**splittedword;
	t_token	*new;
	t_token	*old_curr;
	t_token *new_curr;
	int		i;	

	splittedword = ft_split(curr->word);
	if (!splittedword || !splittedword[0])
		return (curr);
	old_curr = curr;
	i = 0;
	while (splittedword[i])
	{
		new = token_addnew(splittedword[i], 0, 1, 0);
		if (i == 0)
			new_curr = new;
		token_insert_after(curr, new);
		curr = curr->next;
		i++;
	}
	token_lstdelone(head, old_curr, del);
	curr = new_curr;
	return (free(splittedword), curr);
}

void	expansions_search(t_pdata *ptr)
{
	t_token	*curr;
	t_token	*next;
	char	*new;

	curr = ptr->token;
	while (curr)
	{
		next = curr->next;
		if (curr->var == 1 && curr->type != delimiter)
		{
			curr->word = expand(curr->word, &curr->quoting, ptr->env); // null
			if (!curr->word)
			{
				free(curr->word);
				curr->word = ft_strdup("");
			}
			curr = subtokenizer(&ptr->token, curr);
			re_definer(curr);
		}
		curr = next;
	}
}
