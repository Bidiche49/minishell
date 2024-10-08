/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:12:58 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/16 05:12:59 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Delete the env stored at the end
 *
 */
void	del_env(void)
{
	t_env	*tmp;
	t_env	*env;

	tmp = NULL;
	env = *get_env();
	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->val)
			free(tmp->val);
		if (tmp)
			free(tmp);
	}
}

void	base_env(t_env **our_env)
{
	t_env	*tmp;

	tmp = ft_calloc(sizeof(t_env), 1);
	tmp->next = NULL;
	tmp->key = ft_strdup("PWD");
	tmp->val = getcwd(NULL, 0);
	*our_env = tmp;
}

/**
 * @brief depending on the way it is call it will either init the env, add
 * or delete parts of it
 *
 * @param env original env sent to fill our env
 * @param add the string we want to add
 * @param delete the string we want to delete
 * @return the adress of the static making it a singleton
 */
t_env	**handle_env(char **env)
{
	static t_env	*our_env = NULL;

	if (env)
		our_env = init_env(env);
	if (!our_env)
		base_env(&our_env);
	return (&our_env);
}

/**
 * @brief call the function that has the singleton env stored
 *
 * @return the **t_env to the functiun that will need it
 */
t_env	**get_env(void)
{
	return (handle_env(NULL));
}

/**
 * @brief give the env tout the functiun that will handle the env
 *
 * @param env the original env
 */
void	store_env(char **env)
{
	handle_env(env);
}
