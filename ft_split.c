/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:08:01 by okrich            #+#    #+#             */
/*   Updated: 2023/01/05 14:16:37 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count(char *s, char c)
{
	int	x;

	x = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			break ;
		while (*s && *s != c)
			s++;
		x++;
	}
	return (x);
}

void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

char	*get_str(char *s, char c, char **strs)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = sp_strlen(s);
	while (len)
	{
		if (s[i] == c)
			break ;
		i++;
		len--;
	}
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
	{
		free_words(strs);
		return (NULL);
	}
	sp_strlcpy(str, s, i + 1);
	return (str);
}

char	*skip(char *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}

char	**ft_split(char *s, char c)
{
	char	**strs;
	int		count_str;
	int		i;

	if (s == NULL)
		return (NULL);
	s = skip(s, c);
	if (*s == '\0')
		return (NULL);
	count_str = count(s, c);
	strs = malloc(sizeof(char *) * (count_str + 1));
	if (strs == NULL)
		return (NULL);
	i = -1;
	while (++i < count_str)
	{
		strs[i] = get_str(s, c, strs);
		if (strs[i] == NULL)
			return (NULL);
		while (*s && *s != c)
			s++;
		s = skip(s, c);
	}
	strs[i] = NULL;
	return (strs);
}
