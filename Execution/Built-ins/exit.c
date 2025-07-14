/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:14:14 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/14 00:18:52 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_exit_error(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit(255);
}

int	exit_atoi(const char *str, bool *permit)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (is_wspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign *= -1;
	while (*str >= '0' && *str <= '9')
	{
		if (num > (LLONG_MAX - (*str - '0')) / 10)
		{
			*permit = false;
			return -(1);
		}
		num = num * 10 + (*str - '0');
		str++;
	}
	return (((int )num) * sign);
}

int	is_numeric(char *s)
{
	int	i;

	i = 0;
	if (!ft_strcmp(s, ""))
		return (0);
	if (s[0] == '+' || s[0] == '-')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	count_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	exit_builtin(char **cmd, int exit_st)
{
	int		i;
	int		count;
	bool	permit;

	permit = true;
	count = count_arr(cmd);
	i = 0;
	if (count == 1)
		exit(exit_st);
	else if (count > 1 && !is_numeric(cmd[1]))
		print_exit_error(cmd[1]);
	else if (count == 2)
	{
		exit_st = exit_atoi(cmd[1], &permit);
		if (permit)
			exit(exit_st);
		print_exit_error(cmd[1]);
	}
	else
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	return (0);
}
