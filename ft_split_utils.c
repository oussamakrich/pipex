/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:11:09 by okrich            #+#    #+#             */
/*   Updated: 2023/01/05 17:03:19 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	sp_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	sp_strlcpy(char *dst, char *src, int dstsize)
{
	int	j;
	int	i;

	i = sp_strlen(src);
	if (dstsize == 0)
		return (i);
	j = 0;
	while (--dstsize && src[j] != '\0')
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (i);
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

char	*ft_strnjoin(char *s1, char *s2)
{
	char	*join;
	int		len;
	int		len2;

	len = sp_strlen(s1);
	len2 = sp_strlen(s2);
	join = malloc(sizeof(char) * (len + len2 + 1));
	if (join == NULL)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcpy(join + len, s2);
	free (s1);
	return (join);
}
