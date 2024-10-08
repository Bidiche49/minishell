/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ambigous_redirect.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:09:39 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/16 05:18:21 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	message_ambigous(char *val)
{
	int	i;

	i = 1;
	while (val[i] && (val[i] == '_'
			|| (val[i] >= 'A' && val[i] <= 'Z')
			|| (val[i] >= 'a' && val[i] <= 'z')
			|| (val[i] >= '0' && val[i] <= '1')))
	{
		ft_putchar_err(val[i]);
		i++;
	}
	msg(": ambiguous redirect\n");
}

int	var_testing(char *val)
{
	t_env	*env;

	if (!val)
		return (1);
	env = *get_env();
	while (env)
	{
		if (!ft_strncmp(val, env->key, ft_strlen(env->key)))
			return (1);
		env = env->next;
	}
	return (0);
}

int	is_okvar_present(char *val)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (val[i])
	{
		if (val[i] == '$')
		{
			i++;
			while (val[i + j] && (val[i + j] == '_'
					|| (val[i + j] >= 'A' && val[i + j] <= 'Z')
					|| (val[i + j] >= 'a' && val[i + j] <= 'z')
					|| (val[i + j] >= '0' && val[i + j] <= '1')))
				j++;
			if (var_testing(val + i))
				return (1);
			i = i + j - 1;
			j = 0;
		}
		i++;
	}
	return (0);
}

int	ambigous_redirect_checker(t_val *data)
{
	t_val	*tmp;
	t_val	*tmp2;

	tmp = data;
	tmp2 = tmp;
	while (tmp && tmp->val[0] != '$')
	{
		tmp2 = tmp;
		tmp = tmp->next;
	}
	if (tmp && tmp2->val
		&& (!ft_strcmp(tmp2->val, "<") || !ft_strcmp(tmp2->val, ">>")
			|| !ft_strcmp(tmp2->val, ">")) && tmp2->next->val[0] == '$'
		&& !is_okvar_present(tmp2->next->val))
	{
		message_ambigous(tmp2->next->val);
		return (1);
	}
	return (0);
}
