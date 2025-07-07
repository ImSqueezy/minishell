/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <aouaalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:48:08 by aouaalla          #+#    #+#             */
/*   Updated: 2025/07/07 14:54:10 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	size(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

char	*get_home(t_env *head, char *key)
{
	t_env	*curr;

	curr = head;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

void	set_saved_pwd(t_gdata *data, char *cwd)
{
	t_env	*curr;

	free(data->saved_pwd);
	data->saved_pwd = ft_strdup(cwd);
	curr = data->env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, "PWD"))
		{
			free(curr->value);
			curr->value = ft_strdup(cwd);
			break ;
		}
		curr = curr->next;
	}
}

void	update_wd(t_gdata *data, char *old_pwd)
{
	t_env	*curr;
	bool	found;
	char	buf[1024];

	found = false;
	if (getcwd(buf, 1024) == NULL)
	{
		perror("getcwd");
		return ;
	}
	set_saved_pwd(data, buf);
	curr = data->env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, "OLDPWD"))
		{
			free(curr->value);
			curr->value = ft_strdup(old_pwd);
			found = true;
		}
		curr = curr->next;
	}
	if (!found)
		env_addback(&data->env, env_addnew("OLDPWD", old_pwd));
}

int	cd(t_gdata *data, char **cmd)
{
	char	*path;
	char	old_path[1024];

	if (size(cmd) > 1)
		path = cmd[1];
	else
	{
		path = get_home(data->env, "HOME");
		if (!path)
			return (ft_putendl_fd("minshell: cd: HOME not set", 2), 1);
	}
	getcwd(old_path, 1024);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minshell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		return (ft_putstr_fd(strerror(errno), 2), ft_putchar_fd('\n', 2), 1);
	}
	return (update_wd(data, old_path), 0);
}
