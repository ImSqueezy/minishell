/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:01:37 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/12 18:50:58 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	equoting_traffic(char quote, char *prev)
{
	if (!*prev && (quote == '\'' || quote == '"'))
		*prev = quote;
	else if (quote && *prev == quote)
		*prev = 0;
}

static char	*expand(t_pdata *pdata, t_gdata *gdata, char *word, int quoting)
{
	t_pdata	var;
	int		i;
	char	*afterd;
	char	*newstr;
	char	*tmp;

	(1) && (newstr = NULL, afterd = NULL, i = 0, var.prev = 0);
	while (word[i])
	{
		equoting_traffic(word[i], &var.prev);
		if (word[i] == '$' && var.prev != '\'')
		{
			i++;
			afterd = getenv_value(pdata, &word[i], &i, gdata->exit);
			if (afterd) {
				tmp = newstr;
				newstr = ft_strnjoin(newstr, afterd, ft_strlen(afterd));
				free(tmp);
			}
			free(afterd);
			i--;
		}
		else
		{
			tmp = newstr;
			newstr = ft_strnjoin(newstr, &word[i], 1);
			free(tmp);
		}
		i++;
	}
	return (newstr);
}

static t_token	*subtokenizer(t_token **head, t_token *curr, t_token *prev)
{
	char	**splittedword;
	t_token	*new;
	t_token	*old_curr;
	t_token	*new_curr;
	int		i;

	splittedword = ft_split(curr->word);
	if (!splittedword || !splittedword[0])
		return (curr);
	(1) && (i = 0, old_curr = curr);
	while (splittedword[i])
	{
		if ((prev && _isred(prev->type)) )
			return (ft_free(splittedword), curr);
		new = sub_token_addnew(splittedword[i], curr);
		if (i == 0)
			new_curr = new;
		token_insert_after(curr, new);
		(1) && (i += 1, curr = curr->next);
	}
	token_lstdelone(head, old_curr, del);
	curr = new_curr;
	if (curr->quoting > 1)
	{
		free(curr->word);
		curr->word = quote_removal(curr, curr->word);
	}
	return (free(splittedword), curr);
}

static void	quote_preserver(t_token *lst)
{
	t_token	*curr;
	t_token	*next;
	char	*tmp;

	curr = lst;
	while (curr)
	{
		next = curr->next;
		if (!ft_strcmp(curr->word, "echo") && next)
		{
			while (next && next->type != PIPE)
			{
				tmp = next->word;
				next->word = quote_removal(next, next->word);
				free(tmp);
				next->quoting = -3;
				next = next->next;
			}
		}
		curr = next;
	}
}

void	expansions_search(t_pdata *pdata, t_gdata *gdata)
{
	t_token	*curr;
	t_token	*next;
	char	*new;
	char	*tmp;

	export_threater(pdata->token);
	curr = pdata->token;
	while (curr)
	{
		next = curr->next;
		if (curr->var == 1 && curr->type != delimiter)
		{
			tmp = curr->word;
			curr->word = expand(pdata, gdata, curr->word, curr->quoting);
			free(tmp);
			if (!curr->word)
				curr->word = ft_strdup("");
			curr = subtokenizer(&pdata->token, curr, curr->prev);
			re_definer(curr);
		}
		curr = next;
	}
	suppress_emptytokens(&pdata->token);
}
