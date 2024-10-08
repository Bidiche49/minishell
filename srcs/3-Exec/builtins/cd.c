/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:10:48 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/16 05:10:51 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	modify_pwd(void)
{
	t_env	*env;
	t_env	*env_tmp;

	env = *get_env();
	env_tmp = env;
	while (env_tmp && ft_strcmp(env_tmp->key, "PWD"))
		env_tmp = env_tmp->next;
	while (env && ft_strcmp(env->key, "OLDPWD"))
		env = env->next;
	if (env && env->val && env_tmp && env_tmp->val)
	{
		free(env->val);
		env->val = ft_strdup(env_tmp->val);
	}
	if (env_tmp && env_tmp->val)
	{
		free(env_tmp->val);
		env_tmp->val = getcwd(NULL, 0);
	}
	if (env_tmp)
		if (!env_tmp->val)
			return (g_error = 127, msg("getcwd fail\n"), 1);
	return (0);
}

/**
 * @brief behave like the cmd cd, changing the directory from wich we operate
 *
 * @param option possible option is a path to a directory
 * @return int
 */
int	b_in_cd(t_val *option, int infile, int outfile)
{
	g_error = 0;
	if (infile != STDIN_FILENO || outfile != STDOUT_FILENO)
	{
		if (outfile == STDOUT_FILENO)
		{
			if (chdir(option->val) == -1)
			{
				perror(NULL);
				g_error = 1;
				chdir("/");
			}
		}
		return (1);
	}
	if (!option || lst_size_val(option) > 1 || option->val[0] == '-')
		return (g_error = 1, msg("error in cd arg\n"), 1);
	if (chdir(option->val) == -1)
	{
		perror(NULL);
		g_error = 1;
		chdir("/");
	}
	modify_pwd();
	return (1);
}
