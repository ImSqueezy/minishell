/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:05:11 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/09 13:08:25 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strnjoin(const char *s1, const char *s2, int n)
{
	char	*new;
	size_t	j;
	size_t	i;
	size_t	size;

	if (!s1)
		return (ft_strndup(s2, n));
	else if (!s2)
		return (ft_strndup(s1, n));
	size = ft_strlen(s1) + n + 1;
	new = malloc(size * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i] && i < n)
		new[j++] = s2[i++];
	new[j] = '\0';
	return (new);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


int	token_size(t_token *ptr)
{
	int	i;

	i = 0;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

int	_isred(char c)
{
	return (c == 2 || c == 3 || c == 4 || c == 5 || c == 6);
}

int	empty_value(char *str)
{
	char	*value;

	value = get_value(str);
	if (ft_strlen(value) == 0)
		return (free(value), 1);
	return (0);
}
