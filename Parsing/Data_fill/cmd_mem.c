#include "../../minishell.h"

static void	free_red(t_red *red)
{
	if (!red)
		return ;

	free(red->fname);
	free(red->heredoc_string);
	free(red);
}

static void	free_reds(t_red *reds)
{
	t_red	*tmp;

	while (reds)
	{
		tmp = reds->next;
		free_red(reds);
		reds = tmp;
	}
}

static void free_str_array(char **arr)
{
	int i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	tcmd_lstclear(t_cmd **lst)
{
	t_cmd	*tmp;

	if (!lst || !*lst)
		return;
	while (*lst)
	{
		tmp = (*lst)->next;
		free_str_array((*lst)->cmd);
		free_reds((*lst)->reds);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
