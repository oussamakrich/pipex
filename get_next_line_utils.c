/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:13:04 by okrich            #+#    #+#             */
/*   Updated: 2023/01/10 12:42:38 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

ssize_t	get_strlen(char *str)
{
	ssize_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*get_strncpy(char *dst, char *src, ssize_t dstsize)
{
	ssize_t	j;
	ssize_t	i;

	i = get_strlen(src);
	if (dstsize == 0)
		return (dst);
	j = 0;
	while (dstsize-- && src[j] != '\0')
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

char	*get_strnjoin(char *s1, char *s2, ssize_t i)
{
	char	*join;
	ssize_t	len;

	len = get_strlen(s1);
	join = malloc(sizeof(char) * (len + i + 1));
	if (join == NULL)
		return (NULL);
	get_strncpy(join, s1, len);
	get_strncpy(join + len, s2, i);
	free (s1);
	return (join);
}

char	*ft_strndup(char *s1, ssize_t n, ssize_t *fail)
{
	int		len;
	char	*dst;

	len = get_strlen(s1);
	if (s1 == NULL)
		return (NULL);
	dst = malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
	{
		*fail = -1;
		return (NULL);
	}
	if (n == -1)
		n = len;
	get_strncpy(dst, s1, n);
	return (dst);
}
