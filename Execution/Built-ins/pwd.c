/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:05:47 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/11 22:09:16 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd(void)
{
	char	buf[1024];

	if (getcwd(buf, 1024) == NULL)
		ft_putendl_fd(buf, 1);
	else
		return (ft_putendl_fd(buf, 1), 1);
	return (0);
}
