/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:13:03 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/05 11:58:02by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_env(char **env)
{
	char	*tmp;
	int		len;
	int		i;
	int		j;

	(1) && (i = 0, len = 0);
	while (env[i++])
		len++;
	i = -1;
	while (++i < len - 1)
	{
		j = -1;
		while (++j < len - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
				(1) && (tmp = env[j], env[j] = env[j + 1], env [j + 1] = tmp);
		}
	}
	i = -1;
	while (env[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
	}
}

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
		(1) && (i++, curr= curr->next);
	}
	env[i] = NULL;
	print_env(env);
}

int	check_symbols(char *identifier)
{
	size_t	len;

	len = ft_strlen(identifier);
	if (len == 2)
	{
		if (identifier[0] == '+' && identifier[1] == '=')	
			return (1);
	}
	else if (len == 1)
	{
		if (identifier[0] == '=')	
			return (1);
	}
	return (0);
}

int	keychecker(char *arg, bool *key_status)
{
	int	i;
	char *key_holder;
	char *identifier;

	i = 0;
	while (arg[i] && ft_isalnum(arg[i]))
		i++;
	if (!arg[i])
		return (*key_status = true, 0);
	key_holder = ft_strndup(arg, i);
	(1) && (arg += i, i = 0);
	if (arg[i] && arg[i] == '+' && arg[i + 1] && arg[i + 1] == '=')
		i += 2;
	else if (arg[i] && arg[i] == '=')
		i++;
	identifier = ft_strndup(arg, i++);
	if (!check_symbols(identifier))
		return (free(identifier), free(key_holder), *key_status = false, 1);
	free(identifier);
	free(key_holder);
	return (*key_status = true, 0);
}

char	*append_value(char *old_value, char *to_append)
{
	char	*new;
	int		i, j;

	if (!old_value)
		return (ft_strdup(to_append));
	new = malloc(ft_strlen(old_value) + ft_strlen(to_append) + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (old_value[i])
		new[j++] = old_value[i++];
	ft_strlcpy(new + j, to_append, ft_strlen(to_append) + 1);
	j += ft_strlen(to_append);
	new[j] = '\0';
	return (free(old_value), new);
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
	return (free(new_key), 0);
}

int	export(t_gdata *data)
{
	bool	permit;
	char	**args;
	char	*key;
	char	*value;
	int		i;

	(1) && (i = 1, permit = false, args = data->cmds->cmd);
	if (args[i] == NULL)
		return (print_sortedenv(data->env), 0);
	while (args[i])
	{
		key = get_key(args[i]);
		value = get_value(args[i]);
		if (ft_isdigit(*key) || keychecker(args[i], &permit) || *args[i] == '=')
		{
			printf(INVALID_IDENTIFIER, args[i]);
			data->exit = 1;
		}
		if (permit)
			data->exit = append_env_value(data->env, key, value);
		free(value);
		free(key);
		i++;
	}
	return (data->exit);
}
