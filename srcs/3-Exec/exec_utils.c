/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:11:45 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/16 05:11:47 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_exec(char *cmd)
{
	int	res;

	g_error = 126;
	if (!ft_strcmp(cmd, "."))
		return (msg("Minishell~ .: filename argument required\n"), NULL);
	else if (!ft_strcmp(cmd, ".."))
		return (msg("..: command not found\n"), NULL);
	else if (!ft_strcmp(cmd, "./"))
		return (msg("Minishell~ ./: Is a directory\n"), NULL);
	res = access(cmd, 1);
	if (res >= 0)
		return (ft_strdup(cmd));
	return (perror(cmd), NULL);
}

/**
 * @brief strdup but modified to make env variable style
 *
 * @param env
 * @return char*
 */
char	*ft_strdup_env(t_env *env)
{
	char	*str;
	int		i;
	int		j;
	int		size;

	size = 0;
	size += ft_strlen(env->key);
	size += ft_strlen(env->val);
	str = ft_calloc(size + 1, sizeof(char));
	if (str == 0)
		return (NULL);
	i = -1;
	j = -1;
	while (++i <= size)
	{
		if (i < ft_strlen(env->key) && env->key[i])
			str[i] = env->key[i];
		else if (i == ft_strlen(env->key) && !env->key[i] && ++j == 0)
			str[i] = '=';
		else
			str[i] = env->val[j++];
	}
	str[i] = '\0';
	return (str);
}

/**
 * @brief make envp** needed for the execve functiun
 *
 * @return char**
 */
char	**make_env_tab(void)
{
	char	**start;
	char	**tab;
	t_env	*env;
	int		size;

	env = *get_env();
	size = lst_size(env);
	tab = ft_calloc(sizeof(char *), (size + 1));
	if (!tab)
		return (NULL);
	tab[size] = NULL;
	start = tab;
	while (env)
	{
		*tab = ft_strdup_env(env);
		tab++;
		env = env->next;
	}
	tab = NULL;
	return (start);
}

/**
 * @brief make char** of the cmd needed for the execve functiun
 *
 * @param cmd
 * @return char**
 */
char	**make_cmd_tab(t_val *cmd)
{
	char	**tab;
	char	**tmp;

	tab = malloc(sizeof(char *) * (lst_size_val(cmd) + 1));
	if (!tab)
		return (NULL);
	tab[lst_size_val(cmd)] = NULL;
	tmp = tab;
	while (cmd)
	{
		*tmp = ft_strdup(cmd->val);
		cmd = cmd->next;
		tmp++;
	}
	return (tab);
}

/**
 * @brief look if the functiun called has a path that can be used for execve
 *
 * @param val
 * @param env
 * @return the path if founded else null
 */
char	*pathfinder(char *val, char **env)
{
	char	**path;
	char	*tmp;
	char	*cmd;
	int		i;
	int		j;

	j = -1;
	i = -1;
	tmp = NULL;
	while (env[++i])
		if (ft_strnstr(env[i], "PATH", 4) != NULL)
			tmp = ft_strdup(&env[i][5]);
	if (!tmp)
		return (error_cmd(val), NULL);
	path = ft_split2(tmp, ':');
	while (path[++j])
	{
		tmp = ft_strjoin (path[j], "/");
		cmd = ft_strjoin (tmp, val);
		free(tmp);
		if (access(cmd, 0) == 0)
			return (cmd);
		free(cmd);
	}
	return (free_tab(path), error_cmd(val), NULL);
}
