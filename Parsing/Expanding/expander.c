/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:01:37 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/15 19:28:43 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand(t_pdata *pdata, t_gdata *gdata, char *word)
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
			if (afterd)
				newstr = str_setter(newstr, afterd, ft_strlen(afterd));
			free(afterd);
			i--;
		}
		else
			newstr = str_setter(newstr, &word[i], 1);
		i++;
	}
	return (newstr);
}

static void	sub_quote_removal(t_token *new_curr)
{
	t_token	*curr;
	char	*tmp;

	curr = new_curr;
	if (curr->quoting > 1)
	{
		tmp = curr->word;
		curr->word = quote_removal(curr, curr->word);
		free(tmp);
	}
}

static t_token	*subtokenizer(t_token **hd, t_token *curr, t_token *prev, int i)
{
	char	**splittedword;
	char	*tmp;
	t_token	*new;
	t_token	*old_curr;
	t_token	*new_curr;

	splittedword = ft_split(curr->word, curr->split_permit);
	if (!splittedword || !splittedword[0])
		return (curr);
	old_curr = curr;
	while (splittedword[i])
	{
		if (prev && _isred(prev->type))
			return (ft_free(splittedword), curr);
		new = sub_token_addnew(splittedword[i], curr);
		if (i == 0)
			new_curr = new;
		token_insert_after(curr, new);
		(1) && (i += 1, curr = curr->next);
	}
	token_lstdelone(hd, old_curr, del);
	sub_quote_removal(new_curr);
	return (free(splittedword), curr);
}

void	expand_re_definer(t_token *lst)
{
	t_token	*curr;
	t_token	*prev;
	int		file_onwards;

	curr = lst;
	while (curr)
	{
		prev = curr->prev;
		if (curr->type == 0 && (!prev || prev->type == PIPE
				|| prev->type == command || prev->type == delimiter))
			curr->type = command;
		else if (curr->type == 0 && _isred(prev->type))
			curr->type = file;
		curr = curr->next;
	}
}

void	expansions_search(t_pdata *pdata, t_gdata *gdata)
{
	t_token	*curr;
	t_token	*next;
	char	*new;
	char	*tmp;

	export_threater(pdata->token, gdata->env);
	curr = pdata->token;
	while (curr)
	{
		next = curr->next;
		if (curr->var == 1 && curr->type != delimiter)
		{
			tmp = curr->word;
			curr->word = expand(pdata, gdata, curr->word);
			free(tmp);
			if (!curr->word)
				curr->word = ft_strdup("");
			curr = subtokenizer(&pdata->token, curr, curr->prev, 0);
			expand_re_definer(pdata->token);
		}
		curr = next;
	}
	suppress_emptytokens(&pdata->token);
}
