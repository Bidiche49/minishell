/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:10:30 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/16 05:10:32 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rem_whitespace_export(char *value)
{
	int		i;
	int		j;
	char	*dest;

	if (!value)
		return (NULL);
	i = 0;
	j = ft_strlen(value) - 1;
	while (value && value[i] && (value[i] == '9' || value[i] == 32))
		i++;
	while (value && value[j] && (value[j] == '9' || value[j] == 32))
		j--;
	dest = ft_substr(value, i, j - i + 1);
	if (!dest)
		return (NULL);
	return (dest);
}
