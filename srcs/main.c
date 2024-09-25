/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:13:42 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/16 05:13:43 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

int	main(int ac, char **av, char **envp)
{
	char	*buf;

	(void)av;
	(void)ac;
	store_env(envp);
	set_shlvl();
	init_signal1();
	buf = NULL;
	while (1)
	{
		buf = readline("Minishell ~");
		if (!buf)
			break ;
		else
		{
			add_history(buf);
			split_pars(buf);
		}
	}
	del_env();
	rl_clear_history();
	write(STDOUT_FILENO, "exit\n", 5);
	return (g_error);
}
