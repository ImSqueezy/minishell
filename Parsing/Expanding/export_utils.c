/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:36:06 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/09 14:40:05 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_special_dollars(char *str)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (!ft_isalnum(str[i + 1]) && (str[i + 1] != '?')))
			count += 2;
		i++;
	}
	return count;
}

int	valid_identifier(char *key)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strchr(key, '$');
	if (!tmp)
		return (1);
	while (tmp[i])
	{
		if (!ft_isalnum(tmp[i]) || tmp[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}

char *epreserve_key(char *str, int i, int j)
{
	char *new;

	new = malloc(ft_strlen(str) + count_special_dollars(str) + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && (!ft_isalnum(str[i + 1]) && str[i + 1] != '?'))
		{
			new[j++] = '\'';
			new[j++] = str[i++];
			new[j++] = '\'';
		}
		new[j++] = str[i++];
	}
	new[j] = '\0';
	return (new);
}
