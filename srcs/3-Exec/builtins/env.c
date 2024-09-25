/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:11:02 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/16 05:11:04 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_cmd(int fd)
{
	t_env	*env;

	env = *get_env();
	while (env)
	{
		if (env->val)
		{
			ft_putstr_fd(fd, env->key);
			write(fd, "=", 1);
			ft_putstr_fd(fd, env->val);
			write(fd, "\n", 1);
		}
		env = env->next;
	}
	return (g_error = 0, 1);
}
