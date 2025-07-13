/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:13:03 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/14 00:17:08 by aouaalla         ###   ########.fr       */
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
			env[i] = get_export_env(curr);
		else
			env[i] = ft_strdup(curr->key);
		(1) && (i++, curr = curr->next);
	}
	env[i] = NULL;
	print_env(env);
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
	free(new_key);
	return (0);
}

int	set_permit(char *arg, char *key, char *value, bool *permit)
{
	static int	last_res;

	if (ft_isdigit(*key) || keychecker(arg, permit) || *arg == '=')
	{
		printf(EINVALID_IDENTIFIER, arg);
		free(value);
		last_res = 1;
		return (1);
	}
	if (last_res == 1)
		return (1);
	return (0);
}

int	export(t_gdata *data, t_cmd *cmd, int i)
{
	bool	permit;
	char	**args;
	char	*key;
	char	*value;
	int		res;

	(1) && (permit = false, args = cmd->cmd, res = 0);
	if (args[1] == NULL)
		return (print_sortedenv(data->env), 0);
	while (args[++i])
	{
		key = get_key(args[i]);
		value = get_value(args[i]);
		res = set_permit(args[i], key, value, &permit);
		if (permit == true)
		{
			if (res == 0)
				res = append_env_value(data->env, key, value);
			free(value);
		}
		free(key);
	}
	return (res);
}
