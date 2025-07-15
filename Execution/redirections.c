/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadkaou <asadkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:10:06 by asadkaou          #+#    #+#             */
/*   Updated: 2025/07/15 02:10:07 by asadkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_fd(t_red *r, char **file)
{
	int	fd;

	fd = -1;
	if (r->type == heredoc)
	{
		*file = generate_path();
		fd = open(*file, O_CREAT | O_WRONLY, 0644);
		write(fd, r->heredoc_string, ft_strlen(r->heredoc_string));
		close(fd);
		fd = open(*file, O_RDONLY, 0644);
		unlink(*file);
		free(*file);
	}
	else if (r->type == red_in)
		fd = open(r->fname, O_RDONLY);
	else if (r->type == red_out)
		fd = open(r->fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (r->type == append)
		fd = open(r->fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int	handle_redirections(t_red *reds)
{
	char	*file;
	int		fd;

	while (reds)
	{
		if (reds->ambiguous)
			return (ft_putendl_fd("minishell: ambiguous redirect", 2), 0);
		fd = open_fd(reds, &file);
		if (fd < 0)
			return (perror(reds->fname), 0);
		if (reds->type == red_in || reds->type == heredoc)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		reds = reds->next;
	}
	return (1);
}
