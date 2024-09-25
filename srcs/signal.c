/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:13:55 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/16 05:13:56 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler_signal(int sig)
{
	if (sig == SIGQUIT)
		return ;
	if (sig == SIGINT)
	{
		g_error = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signal2(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	init_signal1(void)
{
	signal(SIGINT, &handler_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_heredoc(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	g_error = 128;
	return ;
}
