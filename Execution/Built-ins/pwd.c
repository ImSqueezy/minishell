/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:05:47 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/13 14:33:30 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd(t_gdata *data)
{
	char	buf[1024];

	if (getcwd(buf, 1024))
		ft_putendl_fd(buf, 1);
	else
		return (ft_putendl_fd(data->saved_pwd, 1), 1);
	return (0);
}
