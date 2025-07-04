/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:45:58 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/04 21:26:37 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_dollar(char *s)
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
			equoting_traffic(str[i], &var);
		if (str[i] == '$' && !var)
			count++;
		i++;
	}
	return (count * 2);
}

static void	helpers_setter(bool *value_portion, char *var, char current_char)
{
	if (current_char == '=')
		*value_portion = true;
	if (current_char == '\'' || current_char == '"')
		equoting_traffic(current_char, var);
}

static char	*epreserve_value(char *str, int i, int j)
{
	bool	value_portion;
	char	*new;
	char	var;

	if (empty_value(str))
		return (ft_strjoin(str, "\"\""));
	new = malloc(ft_strlen(str) + count_dollar(str) + 1);
	if (!new)
		return (NULL);
	(1) && (var = 0, value_portion = false);
	while (str[i])
	{
		helpers_setter(&value_portion, &var, str[i]);
		if (value_portion && str[i] == '$' && !var)
		{
			(1) && (new[j++] = '"', new[j++] = str[i++]);
			while (ft_isalnum(str[i]) || str[i] == '_')
				new[j++] = str[i++];
			new[j++] = '"';
			continue ;
		}
		new[j++] = str[i++];
	}
	new[j] = '\0';
	return (free(str), new);
}

static void	value_preserver(t_token *export)
{
	t_token	*curr;
	char	*key;
	char	*value;
	int		i;
	int		j;

	(1) && (i = 0, j = 0, curr = export->next);
	while (curr)
	{
		key = get_key(curr->word);
		if (!ft_strchr(key, '\"') && !ft_strchr(key, '\'')
			&& !ft_strchr(key, '$'))
		{
			curr->word = epreserve_value(curr->word, i, j);
			value = get_value(curr->word);
			if (!ft_strcmp(value, "\"\""))
				curr->var = 3;
			free(value);
		}
		free(key);
		curr = curr->next;
	}
}

void	export_threater(t_token	*head)
{
	t_token	*curr;
	bool	redirect_exists;
	int		strcmp;
	int		count;

	count = 0;
	curr = head;
	redirect_exists = false;
	while (curr)
	{
		if (curr->type == red_out || curr->type == red_out
			|| curr->type == append || curr->type == heredoc)
			redirect_exists = true;
		curr = curr->next;
	}
	curr = head;
	while (curr)
	{
		strcmp = ft_strcmp(curr->word, "export");
		if ((!strcmp && count == 0)
			|| (!strcmp && redirect_exists && count > 0))
			value_preserver(curr);
		(1) && (count++, curr = curr->next);
	}
}
