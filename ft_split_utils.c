/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:11:09 by okrich            #+#    #+#             */
/*   Updated: 2023/01/11 19:27:17 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

ssize_t	ft_strlen(char *str)
{
	ssize_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strncpy(char *dst, char *src, ssize_t dstsize)
{
	ssize_t	j;
	ssize_t	i;

	i = ft_strlen(src);
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

char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2, char c)
{
	char	*join;
	int		len;
	int		len2;
	int		i;

	i = 1;
	if (c == '/')
		i = 2;
	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = malloc(sizeof(char) * (len + len2 + i));
	if (join == NULL)
		return (NULL);
	ft_strcpy(join, s1);
	if (c == '/')
	{
		join[len] = '/';
		ft_strcpy(join + len + 1, s2);
	}
	else
		ft_strcpy(join + len, s2);
	return (join);
}

char	*get_strnjoin(char *s1, char *s2, ssize_t i)
{
	char	*join;
	ssize_t	len;

	len = ft_strlen(s1);
	join = malloc(sizeof(char) * (len + i + 1));
	if (join == NULL)
		return (NULL);
	ft_strncpy(join, s1, len);
	ft_strncpy(join + len, s2, i);
	free (s1);
	return (join);
}
