/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:00:38 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/14 00:15:25 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_export_env(t_env *curr)
{
	char	*tmp;
	char	*res;

	res = ft_strjoin(curr->key, "=\"");
	tmp = res;
	res = ft_strjoin(res, curr->value);
	free(tmp);
	tmp = res;
	res = ft_strjoin(res, "\"");
	free(tmp);
	return (res);
}

int	keychecker(char *arg, bool *key_status)
{
	int		i;
	char	*key_holder;
	char	*identifier;

	i = 0;
	while (arg[i] && ft_isalnum(arg[i]))
		i++;
	if (!arg[i])
		return (*key_status = true, 0);
	key_holder = ft_strndup(arg, i);
	if (ft_strlen(key_holder) == 0)
		return (free(key_holder), *key_status = false, 1);
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
