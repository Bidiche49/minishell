/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:11:53 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/16 05:11:55 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_cmd(char *cmd)
{
	g_error = 127;
	msg(cmd);
	msg(": command not found\n");
}

char	*fillpath(t_pipex *exec, char **env)
{
	if (exec->cmd->val[0] == '.' || exec->cmd->val[0] == '/')
		return (is_exec(exec->cmd->val));
	else
		return (pathfinder(exec->cmd->val, env));
}

int	is_builtin2(char *cmd, t_pipex *exec, int res)
{
	t_val	*tmp;

	if (!ft_strcmp(cmd, "env"))
		res = env_cmd(exec->fd[1]);
	else if (!ft_strcmp(cmd, "export") && exec->cmd->next)
	{
		tmp = exec->cmd->next;
		while (tmp)
		{
			res = export_cmd(tmp->val, exec->fd[1]);
			tmp = tmp->next;
		}
	}
	else if (!ft_strcmp(cmd, "export") && !exec->cmd->next)
		res = export_cmd(NULL, exec->fd[1]);
	return (res);
}

/**
 * @brief check if the cmd that will be executed is a builtin or not
 *
 * @param cmd the cmd to execute
 * @param exec the struct
 * @return int
 */
int	is_builtin(char *cmd, t_pipex *exec)
{
	int		res;
	t_val	*tmp;

	res = 0;
	g_error = 0;
	if (!ft_strcmp(cmd, "cd"))
		res = b_in_cd(exec->cmd->next, exec->fd[0], exec->fd[1]);
	else if (!ft_strcmp(cmd, "echo"))
		res = b_in_echo(exec->cmd->next, exec->fd[1]);
	else if (!ft_strcmp(cmd, "pwd"))
		res = b_in_pwd(exec->fd[1]);
	else if (!ft_strcmp(cmd, "exit"))
		res = b_in_exit(exec->cmd->next, exec);
	else if (!ft_strcmp(cmd, "unset"))
	{
		tmp = exec->cmd->next;
		while (tmp)
		{
			res = unset_cmd(tmp->val);
			tmp = tmp->next;
		}
	}
	return (is_builtin2(cmd, exec, res));
}
