/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:10:56 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/16 05:10:58 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *val)
{
	if (*val == '-')
		val++;
	else
		return (0);
	if (!*val)
		return (0);
	while (*val)
	{
		if (*val != 'n')
			return (0);
		val++;
	}
	return (1);
}

int	make_check_n(t_val **options)
{
	int	n;

	n = 0;
	while (*options && (*options)->val && check_n((*options)->val))
	{
		*options = (*options)->next;
		n = 1;
	}
	return (n);
}

/**
 * @brief behave like the echo functiun
 *
 * @param options if option 1 is -n then no \n at the end
 * @param fd where to write the output
 * @return int
 */
int	b_in_echo(t_val *options, int fd)
{
	int		n;
	char	*a;

	if (!options)
		return (write(fd, "\n", 1), 1);
	if (options && options->val)
		n = make_check_n(&options);
	while (options)
	{
		if (options->q == 0)
		{
			if (options->val)
				ft_putstr_fd(fd, options->val);
			a = options->val;
			options = options->next;
			if (options && ft_strcmp(" ", a))
				write(fd, " ", 1);
		}
		else
			options = options->next;
	}
	if (!n)
		write(fd, "\n", 1);
	return (1);
}
