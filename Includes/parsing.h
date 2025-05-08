/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:39:54 by aouaalla          #+#    #+#             */
/*   Updated: 2025/04/21 21:39:55 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/*
    - Libft has:
        * unistd
        * stdlib
        * limits
*/
# include "../Libraries/Libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <termios.h>

typedef struct parsing
{
	bool	traffic;
	char	quote;
	char	prev;
}	t_pdata;

char	*spacing(const char *p, t_pdata *data);
size_t	straddlen(const char *p, size_t old_len, t_pdata *data);
void	quoting_traffic(char c, t_pdata *data);
int		isred(char c);
int		isop(char c);

#endif
