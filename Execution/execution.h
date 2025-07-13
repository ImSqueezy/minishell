/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:19:41 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/13 14:38:24 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>


void	executer(t_gdata	*data);
int		echo(char **cmd);
int		env(t_env *head);
int		exit_builtin(char **cmd, int exit_st);
int		export(t_gdata *data, t_cmd *cmd);
int		check_invalid_symbols(char *identifier);
char	*append_value(char *old_value, char *to_append);
void	print_env(char **env);
int		unset(t_gdata *shell, char **ar);
int		cd(t_gdata *data, char **cmd);
int     pwd(t_gdata *data);
char	**ft_execution_split(char const *s, char c);
int		is_built_in(t_cmd *cmd);
int		execute_builtin(t_cmd * current, t_gdata *ptr);
char    *get_env_v(t_env *env, char *key);
#endif