/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:13:03 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/04 21:35:39 by aouaalla         ###   ########.fr       */
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
		if (ft_strlen(curr->value) > 0)
		{
			env[i] = ft_strjoin(curr->key, "=");
			env[i] = set_newstr(env[i], curr->value, ft_strlen(curr->value));
		}
		else
			env[i] = ft_strdup(curr->key);
		(1) && (i++, curr= curr->next);
	}
	env[i] = NULL;
	print_env(env);
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
		if (ft_is_symbol(key[i]) || (key[i] == '+' && key[i + 1] != '\0'))
			return (1);
		i++;
	}
	return (0);
}

int	checkinvalid_identifier(char *key, bool *key_status)
{
	if (ft_isdigit(*key) || check_symbols(key))
		return (*key_status = false, 1);
	return (*key_status = true, 0);
}

void	set_key(t_env *head, char *key, char *value)
{
	bool	permitted;
	t_env	*curr;
	char	*tmp;

	permitted = true;
	bool	key_exists = false;
	curr = head;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key) && ft_strlen(value))
			key_exists = true;
		if (!ft_strcmp(curr->key, key) && !ft_strlen(value))
			permitted = false;
		curr = curr->next;
	}
	if (permitted && !key_exists)
		env_addback(&head, env_addnew(key, value));
	else
	{
		// replace value
		return ;
	}
}

int	export(t_gdata *data)
{
	char	**args;
	char	*key;
	int		i;
	bool	permit;

	permit = false;
	args = data->cmds->cmd;
	if (args[1] == NULL)
		return (print_sortedenv(data->env), 0);
	i = 1;
	while (args[i])
	{
		key = get_key(args[i]);
		if (checkinvalid_identifier(key, &permit) || *args[i] == '=')
			printf(INVALID_IDENTIFIER, args[i]);
		if (permit)
			set_key(data->env, key, get_value(args[i]));
		free(key);
		i++;
	}
	return (0);
}
