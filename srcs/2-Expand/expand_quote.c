/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:09:49 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/16 05:09:52 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief * -1 for char in negative
 *
 * @param data
 */
void	back_to_positive(t_val *data)
{
	int	i;

	i = 0;
	while (data->val[i])
	{
		if (data->val[i] < 0)
			data->val[i] = data->val[i] * -1;
		i++;
	}
}

/**
 * @brief Clear empty content in data
 *
 * @param data
 */
int	clean_data(t_val **data)
{
	t_val	*tmp;
	t_val	*tmp2;

	tmp2 = *data;
	tmp = tmp2;
	place_data(data);
	while (tmp)
	{
		if (!(*(tmp->val)) && (!(*data) || ft_strcmp((*data)->val, "echo")))
		{
			tmp2->next = tmp->next;
			tmp2 = tmp->next;
			free(tmp->val);
			free(tmp);
			tmp = tmp2;
		}
		if (tmp)
		{
			tmp2 = tmp;
			tmp = tmp->next;
		}
	}
	if (!(*data))
		return (1);
	return (0);
}

/**
 * @brief Increment in case of simple quote
 *
 * @param content
 * @param i
 * @return int
 */
int	simple_increment(char *content, int *i)
{
	(*i)++;
	while (content[*i] != '\'')
	{
		if (!content[*i])
			return (1);
		(*i)++;
	}
	return (0);
}

/**
 * @brief Check if we have the right number of quotes
 *
 * @param content
 * @return int
 */
int	is_error_qm(char *content, t_val *tmp, t_val *tmp_prev)
{
	int		i;

	i = -1;
	while (content[++i])
	{
		if (content[i] == '\'')
			if (simple_increment(content, &i))
				return (1);
		if (content[i] == '"')
		{
			i++;
			while (content[i] != '"')
			{
				if (!content[i])
					return (1);
				i++;
			}
		}
	}
	if (tmp->token == LIMITOR)
		return (0);
	if (quote_parsing(tmp->val, tmp)
		|| (!tmp_prev && expand_space(tmp->val, tmp)))
		return (1);
	return (0);
}

/**
 * @brief Main treatment of expand, calling all parts
 *
 * @param data
 * @return int
 */
int	quote_treatment(t_val *data)
{
	t_val	*tmp;
	t_val	*tmp_prev;

	tmp = data;
	tmp_prev = NULL;
	if (ambigous_redirect_checker(data))
		return (free_lst(data), 0);
	while (tmp)
	{
		if (tmp->token == WORD || tmp->token == FD)
		{
			if (is_error_qm(tmp->val, tmp, tmp_prev))
				return (free_lst(data), 0);
			back_to_positive(tmp);
		}
		else
			tmp_prev = NULL;
		tmp = tmp->next;
	}
	if (!clean_data(&data))
		return (exec(data), 0);
	else
		return (printf("Minishell ~ : command not found\n"), 0);
}
