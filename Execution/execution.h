/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:19:41 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/07 16:19:42 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <errno.h>
# include <string.h>
# define INVALID_IDENTIFIER "minishell: export: `%s': not a valid identifier\n"

void	executer(t_gdata	*data);
int		echo(char **cmd);
int		env(t_env *head);
int		export(t_gdata *data);
int		check_symbols(char *identifier);
char	*append_value(char *old_value, char *to_append);
void	print_env(char **env);
int		unset(t_gdata *shell, char **ar);
int		cd(t_gdata *data, char **cmd);
int		pwd(t_gdata *data);

#endif