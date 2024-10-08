/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:13:07 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/16 05:13:08 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/**
 * @brief free the lst used in the parsing / expand / exec (inside the cmd list)
 *
 * @param data
 */
void	free_lst(t_val	*data)
{
	t_val	*save;

	if (!data)
		return ;
	while (data)
	{
		save = data;
		data = data->next;
		free(save->val);
		free(save);
	}
	data = NULL;
}

/**
 * @brief free the cmd list used in exec
 *
 * @param exec
 */
void	free_lst_exec(t_pipex *exec)
{
	t_pipex	*tmp;

	while (exec)
	{
		if (exec->cmd)
			free_lst(exec->cmd);
		if (exec->redir)
			free_lst(exec->redir);
		if (exec->fd[0] != 0)
			close(exec->fd[0]);
		if (exec->fd[1] != 1)
			close(exec->fd[1]);
		tmp = exec;
		exec = exec->next;
		free(tmp);
	}
}

void	free_wr(char *content, char *nw)
{
	if (content)
		free(content);
	if (nw)
		free(nw);
}

void	free_vr(char *name)
{
	if (name)
		free(name);
}
// void	free_char(char **cmd, char **env, char *path);
