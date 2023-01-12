/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:22:01 by okrich            #+#    #+#             */
/*   Updated: 2023/01/11 19:52:06 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

char	*ft_strndup(char *s1, ssize_t n, ssize_t *fail)
{
	int		len;
	char	*dst;

	len = ft_strlen(s1);
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
	ft_strncpy(dst, s1, n);
	return (dst);
}

ssize_t	check_newline(char *reader)
{
	ssize_t	i;

	i = 0;
	if (reader == NULL)
		return (-1);
	while (reader[i] != '\0')
	{
		if (reader[i] == '\n')
			break ;
		i++;
	}
	if (reader[i] == '\0')
		return (-1);
	return (i + 1);
}

char	*get_resteofline(ssize_t n, char **rest)
{
	char	*tmp;
	char	*line;
	ssize_t	nl;

	line = ft_strndup(*rest, n, &nl);
	if (line == NULL)
		return (NULL);
	if (n < ft_strlen(*rest))
	{
		tmp = ft_strndup(*rest + n, -1, &nl);
		free(*rest);
		if (tmp == NULL)
			return (NULL);
		*rest = tmp;
	}
	else
	{
		free(*rest);
		*rest = NULL;
	}
	return (line);
}

ssize_t	read_and_get_line(ssize_t	n, int fd, char **line, char **rest)
{
	char	*reader;
	ssize_t	pos;

	reader = malloc(BUFFER_SIZE + 1);
	if (reader == NULL)
		return (-1);
	while (n > 0)
	{
		n = read(fd, reader, BUFFER_SIZE);
		if (n <= 0)
			break ;
		reader[n] = '\0';
		pos = check_newline(reader);
		if (pos != -1)
		{
			*line = get_strnjoin(*line, reader, pos);
			if (pos < n && *line != NULL)
				*rest = ft_strndup(reader + pos, -1, &n);
			break ;
		}
		*line = get_strnjoin(*line, reader, n);
		if (*line == NULL)
			break ;
	}
	return (free(reader), n);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	ssize_t		n;

	n = check_newline(rest);
	if (n != -1)
	{		
		line = get_resteofline(n, &rest);
		return (line);
	}
	line = rest;
	rest = NULL;
	n = read_and_get_line(1, fd, &line, &rest);
	if (n == -1)
		return (free(line), NULL);
	return (line);
}
