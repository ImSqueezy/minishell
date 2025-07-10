#include "../minishell.h"

char	*fill_nline(char *n_line, char *o_line, char *value, int key_len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (o_line[i])
	{
		if (o_line[i] == '$' && !k)
		{
			k = 0;
			while (value[k])
				n_line[j++] = value[k++];
			i += key_len + 1;
		}
		if (o_line[i] == '\0')
		{
			n_line[j] = '\0';
			return (n_line);
		}
		n_line[j++] = o_line[i++];
	}
	n_line[j] = '\0';
	return (n_line);
}

char	*e_replace_key(t_env *env, char *line, char *key)
{
	char	*new_line;
	char	*value;
	t_env	*curr;
	
	value = NULL;
	curr = env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
			value = curr->value;
		curr = curr->next;
	}
	if (!value)
		return (line);
	new_line = malloc((ft_strlen(line) - ft_strlen(key) - 1)
		+ ft_strlen(value) + 1);
	if (!new_line)
		return (NULL);
	new_line = fill_nline(new_line, line, value, ft_strlen(key));
	free(line);
	return (new_line);
}

char	*e_expand(t_env *env, char *line)
{
	char	*key;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ')
		{
			key = get_key(&line[++i]);
			line = e_replace_key(env, line, key);
		}
		i++;
	}
	return (line);
}

void	process_heredocs(t_env *env, t_cmd *cmds, int *heredoc_fds)
{
	int		i = 0;
	t_red	*red;
	int		pipefd[2];
	char	*line;

	while (cmds)
	{
		heredoc_fds[i] = -1;
		red = cmds->reds;
		while (red)
		{
			if (red->type == heredoc)
			{
				if (pipe(pipefd) == -1)
				{
					perror("pipe");
					exit(1);
				}
				while (1)
				{
					line = readline("> ");
					if (ft_strchr(line, '$') && cmds->reds->expand)
						line = e_expand(env, line);
					if (!line || ft_strcmp(line, red->fname) == 0)
					{
						free(line);
						break;
					}
					write(pipefd[1], line, strlen(line));
					write(pipefd[1], "\n", 1);
					free(line);
				}
				//close write end
				close(pipefd[1]);

				// save read end
				heredoc_fds[i] = pipefd[0];
			}
			red = red->next;
		}
		i++;
		cmds = cmds->next;
	}
}

// ----------------------------- ENV TO ARRAY -----------------------------
char **env_list_to_array(t_env *env)
{
	int count;
	char **envp;
	t_env *tmp;
	int i;
	char *str;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		str = ft_strjoin(tmp->key, "=");
		if (!str)
			return (NULL);
		envp[i] = ft_strjoin(str, tmp->value);
		free(str);
		if (!envp[i])
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

// ----------------------------- UTILS -----------------------------
static void free_string_array(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char *find_command_in_path(char *cmd)
{
	char **paths;
	char *full_path;
	int i;

	if (!cmd || !*cmd)
		return (NULL);
	paths = ft_execution_split(getenv("PATH"), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
			break;
		full_path = ft_strjoin(full_path, cmd);
		if (!full_path)
			break;
		if (access(full_path, X_OK) == 0)
		{
			free_string_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_string_array(paths);
	return (NULL);
}

int count_cmds(t_cmd *cmds)
{
	int count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

// ----------------------------- PIPES -----------------------------
int **create_pipes(int cmd_count)
{
	int **pipes;
	int i;

	if (cmd_count < 2)
		return (NULL);
	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
	{
		perror("malloc pipes");
		exit(1);
	}
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			perror("malloc pipe pair");
			exit(1);
		}
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
	return (pipes);
}

// ----------------------------- REDIRECTIONS -----------------------------
void handle_redirections(t_red *reds)
{
	int fd;

	while (reds)
	{
		if (reds->ambiguous)
		{
			fprintf(stderr, "minishell: ambiguous redirect\n");
			exit(1);
		}

		// Skip heredocs, they are handled separately
		if (reds->type == heredoc)
		{
			reds = reds->next;
			continue;
		}

		fd = -1;
		if (reds->type == red_in)
			fd = open(reds->fname, O_RDONLY);
		else if (reds->type == red_out)
			fd = open(reds->fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (reds->type == append)
			fd = open(reds->fname, O_WRONLY | O_CREAT | O_APPEND, 0644);

		if (fd < 0)
		{
			perror(reds->fname);
			exit(1);
		}

		// Redirect STDIN or STDOUT
		if (reds->type == red_in)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);

		close(fd);

		reds = reds->next;
	}
}


// ----------------------------- SETUP PIPES -----------------------------
void setup_pipes(int i, int cmd_count, int **pipes)
{
	// int	j;

	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < cmd_count - 1)
		dup2(pipes[i][1], STDOUT_FILENO);

	// WHAT'S THE CORE MEANING OF THIS ??
	//  j = 0;
	//  while (j < cmd_count - 1)
	//  {
	//  	close(pipes[j][0]);
	//  	close(pipes[j][1]);
	//  	j++;
	//  }
}

// ----------------------------- EXECUTE COMMAND -----------------------------
void execute_command(t_gdata *data, t_cmd *cmd)
{
	char *path;
	char **envp;

	if (!cmd || !cmd->cmd || !cmd->cmd[0])
	{
		fprintf(stderr, "Empty command\n");
		exit(127);
	}
	if (ft_strchr(cmd->cmd[0], '/'))
		path = ft_strdup(cmd->cmd[0]);
	else
		path = find_command_in_path(cmd->cmd[0]);
	if (!path)
	{
		fprintf(stderr, "%s: command not found\n", cmd->cmd[0]);
		exit(127);
	}
	envp = env_list_to_array(data->env);
	if (!envp)
	{
		fprintf(stderr, "Failed to prepare environment\n");
		free(path);
		exit(1);
	}
	execve(path, cmd->cmd, envp);
	perror("execve");
	exit(1);
}

// ----------------------------- FORK AND EXECUTE -----------------------------
void fork_and_execute_commands(int cmd_count, int **pipes, int *heredoc_fds, t_cmd *cmds, t_gdata *data)
{
	t_cmd *current;
	pid_t pid;
	int i;
	int saved_stdin;
	int saved_stdout;

	current = cmds;
	i = 0;
	while (i < cmd_count)
	{
		//if node has no command, skip fork/exec, just process heredoc to feed pipe if needed
		if (!current->cmd || !current->cmd[0])
		{
			if (heredoc_fds[i] != -1)
				close(heredoc_fds[i]);
			current = current->next;
			i++;
			continue;
		}

		if (is_built_in(current))
		{
			saved_stdin = dup(STDIN_FILENO);
			saved_stdout = dup(STDOUT_FILENO);

			setup_pipes(i, cmd_count, pipes);

			if (heredoc_fds[i] != -1)
			{
				dup2(heredoc_fds[i], STDIN_FILENO);
				close(heredoc_fds[i]);
			}

			handle_redirections(current->reds);
			execute_builtin(data);

			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);

			if (cmd_count > 1 && i < cmd_count - 1)
				close(pipes[i][1]);
			if (i > 0)
				close(pipes[i - 1][0]);
		}
		else
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(1);
			}
			if (pid == 0)
			{
				setup_pipes(i, cmd_count, pipes);

				if (heredoc_fds[i] != -1)
				{
					dup2(heredoc_fds[i], STDIN_FILENO);
					close(heredoc_fds[i]);
				}

				handle_redirections(current->reds);
				execute_command(data, current);
			}
			if (cmd_count > 1 && i < cmd_count - 1)
				close(pipes[i][1]);
			if (i > 0)
				close(pipes[i - 1][0]);
		}
		current = current->next;
		i++;
	}
}


// ----------------------------- EXECUTE PIPELINE -----------------------------
void execute_pipeline(t_gdata *data)
{
	int	cmd_count;
	int	**pipes;
	int	*heredoc_fds;
	int	i;

	cmd_count = count_cmds(data->cmds);
	heredoc_fds = malloc(sizeof(int) * cmd_count);
	if (!heredoc_fds)
	{
		perror("malloc heredoc_fds");
		exit(1);
	}

	process_heredocs(data->env, data->cmds, heredoc_fds);
	pipes = create_pipes(cmd_count);
	fork_and_execute_commands(cmd_count, pipes, heredoc_fds, data->cmds, data);

	// cleanup
	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
	free(heredoc_fds);

	i = 0;
	while (i < cmd_count)
	{
		wait(NULL);
		i++;
	}
}
