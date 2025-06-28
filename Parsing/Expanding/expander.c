/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:01:37 by aouaalla          #+#    #+#             */
/*   Updated: 2025/06/22 17:52:20 by aouaalla         ###   ########.fr       */
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

int	ft_is_symbol(char c) // $, + and _ aren't included
{
	return (c == '!' || c == '@' || c == '#' || c == '%'
	|| c == '^' || c == '&' || c == '*' || c == '('
	|| c == ')' || c == '-' || c == '=');
}

int	check_symbols(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (ft_is_symbol(key[i]) || (key[i] == '+' && key[i + 1] != '='))
			return (1);
		i++;
	}
	return (0);
}

int	checkinvalid_identifier(char *key)
{
	if (ft_isdigit(*key) || check_symbols(key))
		return (1);
	return (0);
}

int	error_checker(t_token *export)
{
	char	*key;
	bool	error_occurance;
	t_token	*curr;

	curr = export->next;
	error_occurance = 0;
	while (curr)
	{
		key = get_key(curr->word);
		if (checkinvalid_identifier(key) || *curr->word == '=')
		{
			error_occurance = 1;
			printf(INVALID_IDENTIFIER, curr->word);
		}
		free(key);
		curr = curr->next;
	}
	return (error_occurance);
}

char	*preserve_value(char *str, int *quoting)
{
	char	*new;
	bool	equal_exists;
	int		i;
	int		j;

	new = malloc(ft_strlen(str) + 3);
	if (!new)
		return (NULL);
	(1) && (equal_exists = false, i = 0, j = 0);
	while (str[i])
	{
		if (str[i] == '=' && !equal_exists)
			(1) && (equal_exists = true, new[j++] = str[i++], new[j++] = '\'');
		else
			new[j++] = str[i++];
	}
	if (equal_exists)
		new[j++] = '\'';
	new[j] = '\0';
	*quoting = -1;
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
		if (!ft_strcmp(curr->word, "export"))
			if (error_checker(curr))
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
