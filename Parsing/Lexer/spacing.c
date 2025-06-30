/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spacing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:23:19 by aouaalla          #+#    #+#             */
/*   Updated: 2025/06/30 19:48:34 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_whitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	isred(char c)
{
	return (c == '>' || c == '<');
}

int	isop(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

/*
	- string additional length
	> returns additional length of strings if a space will be added to it
		(might check quoting syntax errors here)
	> example: "ls>a", if the string would be "ls > a"
		2 chars will be added then
    	the additional length will return 6 as the new length of the string
*/

static void	space_reds(char *res, const char *c, size_t *i, t_pdata *data)
{
	quoting_traffic(*c, data);
	if (isop(*c) && *c != '|')
	{
		if (*c != data->prev)
			res[(*i)++] = ' ';
		res[(*i)++] = *c;
		if (*(c + 1) && !is_whitespace(*(c + 1)))
			res[(*i)++] = ' ';
	}
	else if (isop(*c) && *c == '|')
	{
		res[(*i)++] = ' ';
		res[(*i)++] = *c;
		if (*(c + 1) && !is_whitespace(*(c + 1)))
			res[(*i)++] = ' ';
	}
	else if (!isop(*c) && !is_whitespace(*c))
	{
		res[(*i)++] = ' ';
		res[(*i)++] = *c;
	}
	if (is_whitespace(*c))
		res[(*i)++] = *c;
}

char	*spacing(const char *p, t_pdata *data)
{
	size_t	i;
	char	*res;

	res = malloc(straddlen(p, ft_strlen(p), data) * sizeof(char) + 1);
	if (!res)
		return (NULL);
	(1) && (i = 0, data->quote = 0, data->prev = 0);
	while (*p)
	{
		quoting_traffic(*p, data);
		if (isop(*p) && !data->quote)
		{
			if (data->prev && !is_whitespace(data->prev) && !isop(data->prev))
				res[i++] = ' ';
			(1) && (res[i++] = *p, data->prev = *p++);
			if (!*p)
				break ;
			space_reds(res, p, &i, data);
		}
		else
			res[i++] = *p;
		(1) && (data->prev = *p, p++);
	}
	res[i] = '\0';
	return (res);
}
