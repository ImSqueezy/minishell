/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spacing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:23:19 by aouaalla          #+#    #+#             */
/*   Updated: 2025/05/08 13:23:19 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/parsing.h"

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
	if (isop(*c) && data->prev == *c && *c != '|')
	{
		res[(*i)++] = *c;
		if (*(c + 1) && *(c + 1) != ' ')
			res[(*i)++] = ' ';
	}
	else if (isop(*c) && *c == '|')
	{
		res[(*i)++] = ' ';
		res[(*i)++] = *c;
		if (*(c + 1) && *(c + 1) != ' ')
			res[(*i)++] = ' ';
	}
	else if (!isop(*c) && *c != ' ')
	{
		res[(*i)++] = ' ';
		res[(*i)++] = *c;
	}
	if (*c == ' ')
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
			if (data->prev && data->prev != ' ' && !isop(data->prev))
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

/*

int main(int ac, char **av)
{
	t_pdata	pdata;
	// char *p = "ls| cat<< e|cat>file1| cat file1";
	// char *p = "\'ls>>a\' || > | && &&cat>>a || \"cat>a\"";
	// char *p = "ls>ls>"; //><<>>|||";
	char *p = ">><<>>|||";
	// char *p = " ls| cat<< e";

	printf("%zu becomes %zu\n", ft_strlen(p), straddlen(p, ft_strlen(p), &pdata));
	char *new = spacing(p, &pdata);
	printf("%s.\n- len = %zu\n", new, ft_strlen(new));
	free(new);
	return (0);
}

*/