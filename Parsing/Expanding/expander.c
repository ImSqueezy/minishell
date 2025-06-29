/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:01:37 by aouaalla          #+#    #+#             */
/*   Updated: 2025/06/29 20:50:30 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parsing.h"

void	equoting_traffic(char quote, char *prev)
{
	if (!*prev && (quote == '\'' || quote == '"'))
		*prev = quote;
	else if (quote && *prev == quote)
		*prev = 0;
}

static char	*expand(char *word, int quoting, t_pdata *ptr)
{
	int		i;
	t_pdata	var;
	char	*afterd;
	char	*newstr;

	(1) && (newstr = NULL, i = 0, var.prev = 0);
	while (word[i])
	{
		equoting_traffic(word[i], &var.prev);
		if (word[i] == '$' && var.prev != '\'')
		{
			i++;
			afterd = getenv_value(&word[i], ptr, &i);
			if (afterd)
				newstr = set_newstr(newstr, afterd, ft_strlen(afterd));
			free(afterd);
			i--;
		}
		else
			newstr = set_newstr(newstr, &word[i], 1);
		i++;
	}
	return (free(word), newstr);
}

static t_token	*subtokenizer(t_token **head, t_token *curr)
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
		new = token_addnew(splittedword[i], curr);
		if (i == 0)
			new_curr = new;
		token_insert_after(curr, new);
		(1) && (i += 1, curr = curr->next);
	}
	token_lstdelone(head, old_curr, del);
	curr = new_curr;
	if (curr->quoting > 1)
		curr->word = quote_removal(curr, curr->word);
	return (free(splittedword), curr);
}

void	expansions_search(t_pdata *ptr)
{
	t_token	*curr;
	t_token	*next;
	char	*new;

	export_threater(ptr->token);
	curr = ptr->token;
	while (curr)
	{
		next = curr->next;
		if (curr->var == 1 && curr->type != delimiter)
		{
			curr->word = expand(curr->word, curr->quoting, ptr);
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
	surpress_emptytokens(&ptr->token);
}
