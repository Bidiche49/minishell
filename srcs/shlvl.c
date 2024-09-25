/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:13:48 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/16 05:13:49 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl(void)
{
	t_env	*env;
	int		lvl;

	env = *get_env();
	while (env)
	{
		if (!ft_strcmp(env->key, "SHLVL"))
			break ;
		env = env->next;
	}
	if (env)
	{
		lvl = ft_atoi(env->val);
		free(env->val);
		lvl++;
		env->val = ft_itoa(lvl);
	}
}
