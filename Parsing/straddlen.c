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
	if (!isop(*p) && !is_whitespace(*p))
		count++;
	else if (isop(*p) && *p != data->prev)
		count++;
	else if (data->prev == *p && *p == '|')
	{
		count++;
		p++;
		if (*p && !is_whitespace(*p))
			count++;
	}
	else if (data->prev == *p && !is_whitespace(*(p + 1)))
		count++;
	return (count);
}

size_t	straddlen(const char *p, size_t old_len, t_pdata *data)
{
	size_t	new_len;

	data->traffic = false;
	data->prev = 0;
	data->quote = 0;
	new_len = 0;
	while (*p)
	{
		quoting_traffic(*p, data);
		if (isop(*p) && !data->quote)
		{
			if (data->prev && !is_whitespace(data->prev) && !isop(data->prev))
				new_len++;
			data->prev = *p++;
			if (!*p)
				break ;
			new_len += redirections_count(p, data);
		}
		(1) && (data->prev = *p, p++);
	}
	return (traffic_monitor(data), old_len + new_len);
}

