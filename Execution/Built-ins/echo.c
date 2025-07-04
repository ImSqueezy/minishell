/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:12:54 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/03 21:12:57 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_arg(char *cmd, bool *print_status, bool *new_line)
{
	int	i;

	i = 0;
	if (cmd[i] == '-' && cmd[i + 1] && !*print_status)
	{
		i = 1;
		while (cmd[i])
		{
			if (cmd[i] != 'n')
				return (*print_status = 1, true);
			i++;
		}
		return (*new_line = 1, false);
	}
	return (*print_status = 1, true);
}

int	echo(char **cmd)
{
	int		i;
	bool	new_line;
	bool	n_arg_processed;
	bool	printed;
	bool	permitted;

	i = 1;
	new_line = false;
	printed = false;
	permitted = false;
	while (cmd[i])
	{
		permitted = check_arg(cmd[i], &printed, &new_line);
		if (permitted == true)
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1])
				ft_putchar_fd(' ', 1);
		}
		i++;
	}
	if (!new_line && printed)
		ft_putchar_fd('\n', 1);
	return (0);
}
