#include "../minishell.h"


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

char *find_command_in_path(char *cmd, t_env *env)
{
	char **paths;
	char *full_path;
	int i;

	if (!cmd || !*cmd)
		return (NULL);
	paths = ft_execution_split(get_env_v(env, "PATH"), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
			break;
		full_path = set_newstr(full_path, cmd, ft_strlen(cmd));
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

char	*generate_path()
{
	int		i;
	char	*str;
	char	*num;

	i = 0;
	while (1)
	{
		num = ft_itoa(i);
		if (!num)
			return ( NULL);
		str = ft_strjoin("/tmp/.here_doc", num);
		free(num);
		if (!str)
			return (NULL);
		if (access(str, F_OK) == -1)
			return (str);
		free(str);
		i++;
	}
}
// ----------------------------- REDIRECTIONS -----------------------------
int handle_redirections(t_red *reds)
{
	char *file;
	int fd;


	while (reds)
	{
		if (reds->ambiguous)
		{
			// fprintf(stderr, "minishell: ambiguous redirect\n");
			ft_putendl_fd("minishell: ambiguous redirect", 2);
			return 0;
		}

		// Skip heredocs, they are handled separately
		fd = -1;
		if (reds->type == heredoc)
		{
			file = generate_path();
			fd = open(file, O_CREAT | O_WRONLY, 0644);
			write(fd, reds->heredoc_string, ft_strlen(reds->heredoc_string));
			close(fd);
			fd = open(file, O_RDONLY, 0644);
			unlink(file);
			free(file);
		}
		else if (reds->type == red_in)
			fd = open(reds->fname, O_RDONLY);
		else if (reds->type == red_out)
			fd = open(reds->fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (reds->type == append)
			fd = open(reds->fname, O_WRONLY | O_CREAT | O_APPEND, 0644);

		if (fd < 0) {
			perror(reds->fname);
			return 0;
		}
		if (reds->type == red_in || reds->type == heredoc)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);

		close(fd);

		reds = reds->next;
	}
	return (1);
}


void command_in_child(t_cmd *cmd ,t_gdata *data)
{
	char *path;
	char **envp;

	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		exit(0);

	if (ft_strchr(cmd->cmd[0], '/'))
		path = ft_strdup(cmd->cmd[0]);
	else
		path = find_command_in_path(cmd->cmd[0], data->env);
	if (!path)
	{
		ft_putstr_fd( cmd->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	envp = env_list_to_array(data->env);
	if (!envp)
	{
		ft_putstr_fd("Failed to prepare environment", 2);
		free(path);
		exit(1);
	}
	if (access(path, X_OK) == -1) {
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putendl_fd(": Permission denied", 2);
		exit(126);
	}
	execve(path, cmd->cmd, envp);
	perror("execve");
	exit(1);
}


int get_exit_status(int pid) {
	int status;
	int signal;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status)) {
		return WEXITSTATUS(status);
	} else if (WIFSIGNALED(status)) {
		signal = WTERMSIG(status);
		if (signal == SIGINT)
			ft_putstr_fd("\n", 1);
		else if (signal == SIGQUIT)
			ft_putendl_fd("Quit", 1);
		return 128 + signal;
	}
	return 1;
}

void reset_fds(t_gdata *data) {
	dup2(data->saved_stdin, STDIN_FILENO);
	dup2(data->saved_stdout, STDOUT_FILENO);
	close(data->saved_stdin);
	close(data->saved_stdout);
}

void single_command(t_gdata *data) { // add builtin handling
	if (!handle_redirections(data->cmds->reds)) {
		data->exit = 1;
		return;
	}
	if (is_built_in(data->cmds)) {
		data->exit = execute_builtin(data->cmds, data);
		return;
	}
	int pid = fork();
	if (pid == -1) {
		perror("fork");
		return ;
	}
	if (pid == 0) {
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		command_in_child(data->cmds, data);
	} else {
		data->exit = get_exit_status(pid);
	}
}

void after_fork(t_gdata *data, t_cmd *current, int *save_read, int *fds) {
	bool first_command;

	first_command = current == data->cmds;
	close(data->saved_stdin);
	close(data->saved_stdout);
	if (!first_command) {
		dup2(*save_read, 0);
		close(*save_read);
	}
	dup2(fds[1], 1);
	close(fds[1]);
	close(fds[0]);
	if (!handle_redirections(current->reds))
		exit(1);
	if (is_built_in(current))
		exit(execute_builtin(current, data));
	else
		command_in_child(current, data);
}


int execute_command(t_cmd *current, t_gdata *data, int *save_read) {
	int pid;
	int fds[2];
	
	if (current->next)
			pipe(fds);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return -1;
	}
	if (pid == 0) { 
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		after_fork(data, current, save_read, fds);
	}
	else {
		if (current != data->cmds)
			close(*save_read);
		*save_read = fds[0];
		close(fds[1]);
	}
	return pid;
}



int count_cmds(t_cmd *cmd) 
{
	int i;

	i = 0;
	while(cmd) {
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void kill_children(int *pids, int current) {
	int i;

	i = 0;
	while(i < current)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	while(wait(NULL) != -1);
}


// ----------------------------- FORK AND EXECUTE -----------------------------
void executer(t_gdata *data)
{
	t_cmd *current ;
	int save_read;
	int i;
	current = data->cmds;
	if (!current) {
		data->exit = 0;
		return;
	}
	signal(SIGINT, SIG_IGN);
	data->saved_stdin = dup(STDIN_FILENO);
	data->saved_stdout = dup(STDOUT_FILENO);
	if (!current->next) { // NEEDS BUILTIN HANDLING
		single_command(data);
		reset_fds(data);
		return;
	}
	save_read = -1;
	i = 0;
	data->pids = malloc((count_cmds(current) + 1) * sizeof(int));
	while (current)
	{
		data->pids[i] = execute_command(current, data, &save_read);
		if (data->pids[i] == -1) {
			reset_fds(data);
			kill_children(data->pids, i);
			free(data->pids);
			return;
		}
		i++;
		current = current->next;
	}
	reset_fds(data);
	data->exit = get_exit_status(data->pids[i - 1]);
	while(wait(NULL) != -1);
	free(data->pids);
}