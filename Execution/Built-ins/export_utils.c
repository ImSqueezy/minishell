/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:50:23 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/07 16:18:07 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
		free(env[i]);
	}
	free(env);
}

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
	print(env);
}

int	check_invalid_symbols(char *identifier)
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
			return (0);
	}
	return (1);
}

char	*append_value(char *old_value, char *to_append)
{
	char	*new;
	int		i;
	int		j;

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
