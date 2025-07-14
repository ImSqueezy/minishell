/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:45:58 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/14 07:09:27 by aouaalla         ###   ########.fr       */
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

static char	*epreserve_value(t_env *env, char *str, int i, int j)
{
	bool	v_portion;
	char	*new;
	char	var;

	if (empty_value(str))
		return (ft_strdup(str));
	new = malloc(ft_strlen(str) + count_dollar(str) + 1);
	if (!new)
		return (NULL);
	(1) && (var = 0, v_portion = false);
	while (str[i])
	{
		helpers_setter(&v_portion, &var, str[i]);
		if (v_portion && str[i] == '$' && !var)
		{
			(1) && (new[j++] = '"', new[j++] = str[i++]);
			while (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?')
				new[j++] = str[i++];
			new[j++] = '"';
			continue ;
		}
		new[j++] = str[i++];
	}
	new[j] = '\0';
	return (new);
}

static void	value_preserver(t_token *export, t_env *env, int i, int j)
{
	t_token	*curr;
	char	*key;
	char	*tmp;

	curr = export->next;
	while (curr)
	{
		key = get_key(curr->word);
		if (!ft_strchr(key, '\"') && !ft_strchr(key, '\'')
			&& !ft_strchr(key, '$'))
		{
			tmp = curr->word;
			curr->word = epreserve_value(env, curr->word, i, j);
			(1) && (curr->split_permit = 0, curr->quoting = 3);
			free(tmp);
		}
		if (!valid_identifier(key))
		{
			tmp = curr->word;
			curr->word = epreserve_key(curr->word, i, j);
			free(tmp);
		}
		free(key);
		curr = curr->next;
	}
}

void	export_threater(t_token	*head, t_env *env)
{
	t_token	*curr;
	int		strcmp;
	int		count;

	count = 0;
	curr = head;
	while (curr)
	{
		strcmp = ft_strcmp(curr->word, "export");
		if (!strcmp && count == 0)
			value_preserver(curr, env, 0, 0);
		(1) && (count++, curr = curr->next);
	}
}
