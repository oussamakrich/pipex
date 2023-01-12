/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:40:01 by okrich            #+#    #+#             */
/*   Updated: 2023/01/11 19:11:22 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	get_doc(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd == -1)
		return (perror(file), free(file), exit(1), 1);
	return (fd);
}

int	ft_heredoc(char **av, char **env, char *file)
{
	int	doc;
	int	fd[2];

	doc = get_doc(file);
	write_in_heredoc(av[0], doc, file);
	if (pipe(fd) == -1)
		return (perror("pipe "), unlink(file), free(file), exit (1), 1);
	first_cmd_heredoc(av[1], env, fd, file);
	return (0);
}

int	write_in_heredoc(char *limiter, int fd, char *file)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			return (unlink("file"), free(file), exit (1), 1);
		if (ft_strcmp(line, limiter, '\n') == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	return (0);
}

int	first_cmd_heredoc(char *cmd, char **env, int *fd, char *file)
{
	int		doc;
	int		id;
	int		p_index;

	id = fork();
	if (id == 0)
	{
		doc = open(file, O_RDONLY);
		if (doc == -1)
			return (perror(file), free(file),
				close(fd[1]), close(fd[0]), exit(1), 1);
		dup2(doc, 0);
		close(doc);
		p_index = get_index_of_path(env);
		nrml_cmd(cmd, env, fd, p_index);
		exit (1);
	}
	wait(NULL);
	close_fd_parent(fd);
	return (0);
}
