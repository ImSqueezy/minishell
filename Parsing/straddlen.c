/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   straddlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:32:15 by aouaalla          #+#    #+#             */
/*   Updated: 2025/05/08 13:32:16 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/parsing.h"

int	quoting_traffic(char c, t_pdata *data)
{
	if (!data->quote && (c == '\'' || c == '"'))
		data->quote = c;
	else if (data->quote && c == data->quote)
		data->quote = 0;
	return (data->quote);
}

static void	traffic_monitor(t_pdata *data)
{
	if (data->quote)
		data->traffic = true;
}

size_t	redirections_count(const char *p, t_pdata *data)
{
	size_t	count;
	
	count = 0;
	if (data->prev == '|' || data->prev != *p)
	{
		count++;
		if (!is_whitespace(p[1]) && p[1] != '\0')
			count++;
	}
	else if (isred(data->prev))
	{
		if (!is_whitespace(p[1]) && p[1] != '\0')
			count++;
	}
	return (count);
}

size_t	straddlen(const char *p, size_t old_len, t_pdata *data)
{
	size_t	new_len;

	ft_memset(data, 0, sizeof(t_pdata));
	new_len = 0;
	while (*p)
	{
		quoting_traffic(*p, data);
		if (isop(*p) && !data->quote)
		{
			if (data->prev && !is_whitespace(data->prev) && !isop(data->prev))
				new_len++;
			data->prev = *p++;
			if (isop(*p))
				new_len += redirections_count(p, data);
			else if (*p != '\0' && !isop(*p) && !is_whitespace(*p))
				new_len++;
		}
		if (!*p)
			break ;
		data->prev = *p++;
	}
	return (traffic_monitor(data), old_len + new_len);
}


// int main(int ac, char **av)
// {
// 	t_pdata	pdata;

// 	// char *p = "ls\t|\t|\ts";
// 	// char *p = "ls| cat<< e|cat>file1| cat file1";
// 	// char *p = "<>";
// 	// char *p = "><";
// 	// char *p = "\'ls>>a\' || >a | && &&cat>>a || \"cat>a\"";
// 	// char *p = "ls>ls>"; //><<>>|||";
// 	char *p = ">><<>>|||";
// 	// char *p = " ls| cat<< e";
// 	// char *p = "<>||\\|";
// 	// char *p = "><|b";

// 	// printf("%zu becomes %zu\n", ft_strlen(p), straddlen(p, ft_strlen(p), &pdata));
// 	char *new = spacing(p, &pdata);
// 	// printf("---------------------\n");
// 	printf("%s.\n- len = %zu\n", new, ft_strlen(new));
// 	char **splitted = ft_split(new);
// 	int i = 0;
// 	while (splitted[i])
// 	{
// 		printf("%s\n", splitted[i]);
// 		i++;
// 	}
// 	printf("size of splitteed %d\n", i);
// 	// twod_free(splitted);
// 	// free(new);
// 	return (0);
// }

