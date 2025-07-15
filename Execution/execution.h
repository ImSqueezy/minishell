/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:19:41 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/15 02:36:21 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>

void	executer(t_gdata *data);
int		echo(char **cmd);
int		env(t_env *head);
int		exit_builtin(char **cmd, int exit_st);
int		export(t_gdata *data, t_cmd *cmd, int i);
int		check_invalid_symbols(char *identifier);
char	*append_value(char *old_value, char *to_append);
void	print_env(char **env);
int		unset(t_gdata *shell, char **ar);
int		cd(t_gdata *data, char **cmd);
int		pwd(t_gdata *data);
char	**ft_execution_split(char const *s, char c);
int		is_built_in(t_cmd *cmd);
int		execute_builtin(t_cmd *current, t_gdata *ptr);
char	*get_env_v(t_env *env, char *key);
char	*get_export_env(t_env *curr);
int		keychecker(char *arg, bool *key_status);
void	single_command(t_gdata *data);
void	reset_fds(t_gdata *data);
int		execute_command(t_cmd *cur, t_gdata *data, int *save_read);
int		get_exit_status(int pid);
char	*find_command_in_path(char *cmd, t_env *env);
char	**env_list_to_array(t_env *env);
void	free_string_array(char **arr);
int		handle_redirections(t_red *reds);
void	command_in_child(t_cmd *cmd, t_gdata *data);
char	*generate_path(void);
void	handle_cmd_not_found(char *cmd);
void	handle_env_failure(char *path);
void	handle_permission_denied(char *cmd);

#endif
