/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:13:03 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/11 21:06:00 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_sortedenv(t_env *ptr)
{
	t_env	*curr;
	char	**env;
	int		i;

	(1) && (i = 0, curr = ptr);
	while (curr)
		(1) && (i++, curr = curr->next);
	env = malloc((i + 1) * sizeof(char *));
	if (!env)
		return ;
	(1) && (i = 0, curr = ptr);
	while (curr)
	{
		if (curr->value)
		{
			env[i] = ft_strjoin(curr->key, "=\"");
			env[i] = set_newstr(env[i], curr->value, ft_strlen(curr->value));
			env[i] = set_newstr(env[i], "\"", 1);
		}
		else
			env[i] = ft_strdup(curr->key);
		(1) && (i++, curr = curr->next);
	}
	env[i] = NULL;
	print_env(env);
}

int	keychecker(char *arg, bool *key_status)
{
	int		i;
	char	*key_holder;
	char	*identifier;

	i = 0;
	while (arg[i] && ft_isalnum(arg[i]))
		i++; // key+a+=
	if (!arg[i])
		return (*key_status = true, 0);
	key_holder = ft_strndup(arg, i);
	arg += i;
	i = 0;
	if (arg[i] && arg[i] == '+' && arg[i + 1] && arg[i + 1] == '=')
		i += 2;
	else if (arg[i] && arg[i] == '=')
		i++;
	identifier = ft_strndup(arg, i);
	if (check_invalid_symbols(identifier))
		return (free(identifier), free(key_holder), *key_status = false, 1);
	free(identifier);
	free(key_holder);
	return (*key_status = true, 0);
}

bool	key_setter(t_env *head, char *key, char *value, bool append)
{
	bool	found;
	t_env	*curr;

	found = false;
	curr = head;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key) && append)
		{
			curr->value = append_value(curr->value, value);
			found = true;
		}
		else if (!ft_strcmp(curr->key, key) && !append && !found && value)
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			found = true;
		}
		else if (!ft_strcmp(curr->key, key) && !append && !found && !value)
			found = true;
		curr = curr->next;
	}
	return (found);
}

int	append_env_value(t_env *head, char *key, char *value)
{
	bool	append;
	t_env	*curr;
	char	*new_key;
	int		i;

	i = 0;
	append = false;
	while (key[i] && key[i] != '+')
		i++;
	new_key = ft_strndup(key, i);
	if (ft_strlen(key) != ft_strlen(new_key))
		append = true;
	if (!key_setter(head, new_key, value, append))
		env_addback(&head, env_addnew(new_key, value));
	else
		free(new_key);
	return (0);
}

int	export(t_gdata *data, t_cmd *cmd)
{
	bool	permit;
	char	**args;
	char	*key;
	char	*value;
	int		i;
	int		res;

	res = 0;
	(1) && (i = 1, permit = false, args = cmd->cmd);
	if (args[i] == NULL)
		return (print_sortedenv(data->env), 0);
	while (args[i])
	{
		key = get_key(args[i]);
		value = get_value(args[i]);
		if (ft_isdigit(*key) || keychecker(args[i], &permit) || *args[i] == '=')
		{
			printf(INVALID_IDENTIFIER, args[i]);
			res = 1;
		}
		if (permit) 
		{
			if (res == 0)
				res = append_env_value(data->env, key, value);
		}
		free(value);
		free(key);
		i++;
	}
	return (res);
}
