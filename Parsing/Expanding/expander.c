/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:01:37 by aouaalla          #+#    #+#             */
/*   Updated: 2025/06/29 15:23:44 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parsing.h"

static void	squoting_traffic(char quote, char *prev)
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
		squoting_traffic(word[i], &var.prev);
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

int	count_dollar(char *s)
{
	char	*str;
	char	var;
	int		count;
	int		i;

	str = ft_strchr(s, '=');
	if (!str)
		return (0);
	(1) && (i = 0, count = 0, var = 0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			squoting_traffic(str[i], &var);
		if (str[i] == '$' && !var)
			count++;
		i++;
	}
	return (count * 2);
}

void	helpers_setter(bool *value_portion, char *var, char current_char)
{
	if (current_char == '=')
		*value_portion = true;
	if (current_char == '\'' || current_char == '"')
		squoting_traffic(current_char, var);
}

char	*preserve_value(char *str, int *quoting)
{
	bool	value_portion;
	char	*new;
	char	var;
	int		i;
	int		j;
	
	new = malloc(ft_strlen(str) + count_dollar(str) + 1);
	if (!new)
		return (NULL);
	(1) && (i = 0, j = 0, var = 0, value_portion = false);
	while (str[i])
	{
		helpers_setter(&value_portion, &var, str[i]);
		if (str[i] == '=')
			value_portion = true;
		if (str[i])
		if (value_portion && str[i] == '$' && !var)
		{
			(1) && (new[j++] = '"', new[j++] = str[i++]);
			while (ft_isalnum(str[i]) || str[i] == '_')
				new[j++] = str[i++];
			new[j++] = '"';
		}
		new[j++] = str[i++];
	}
	new[j] = '\0';
	return (free(str), new);
}

void	value_preserver(t_token *export)
{
	t_token	*curr;
	char	*key;

	curr = export->next;
	while (curr)
	{
		key = get_key(curr->word);
		if (!ft_strchr(key, '\"') && !ft_strchr(key, '\'')
			&& !ft_strchr(key, '$'))
				curr->word = preserve_value(curr->word, &curr->quoting);
		free(key);
		curr = curr->next;
	}
}

void	export_threater(t_token	*head)
{
	t_token	*curr;
	int		count;

	(1) && (count = 0, curr = head);
	while (curr)
	{
		if (!ft_strcmp(curr->word, "export") && count == 0)
			value_preserver(curr);
		if (count > 0)
			return ;
		(1) && (count++, curr = curr->next);
	}
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
}
