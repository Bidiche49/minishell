/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:13:24 by ntardy            #+#    #+#             */
/*   Updated: 2023/09/16 05:13:25 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char			*str;
	size_t			i;
	size_t			j;

	i = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof (char) * i + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (j < (size_t)ft_strlen(s2))
	{
		str[i++] = s2[j];
		j++;
	}
	str[i] = '\0';
	return (str);
}

/**
 * @brief duplicate the string and returns it
 *
 * @param s the string to duplicate
 * @return a copy malloced
 */
char	*ft_strdup(char *s)
{
	char	*str;
	int		i;
	int		size;

	if (!s)
		return (NULL);
	size = 0;
	while (s[size])
		size++;
	str = ft_calloc(sizeof(char *), size);
	i = 0;
	if (str == 0)
		return (NULL);
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/**
 * @brief Compare 2 strings
 *
 * @param s1
 * @param s2
 * @return int
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*word_replacing(int start, int end, char *content, char *new_word)
{
	char	*dest;
	int		i;
	int		j;

	i = -1;
	j = 0;
	dest = ft_calloc((ft_strlen(content) - (end - start))
			+ ft_strlen(new_word), 1);
	if (!dest)
		return (NULL);
	while (content && ++i < start)
		dest[i] = content[i];
	while (new_word && new_word[j])
	{
		dest[i + j] = new_word[j];
		j++;
	}
	while (content && content[end] && content[++end])
	{
		dest[i + j] = content[end];
		i++;
	}
	free_wr(content, new_word);
	return (dest);
}

/**
 * @brief duplicate only the size received from the string
 *
 * @param s the string
 * @param size the size
 * @return the new string of size == size
 */
char	*ft_strndup(const char *s, int size)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof (char) * (size + 1));
	i = 0;
	if (str == 0)
		return (NULL);
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
