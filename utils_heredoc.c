/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:40:01 by okrich            #+#    #+#             */
/*   Updated: 2023/01/10 19:24:13 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int	read_from_heredoc(char **av, int fd)
{
	char	*line;

	if (dup2(fd, 1) == -1)
		return (perror("dup2 "), close(fd), unlink(".here_doc"), exit(1), 1);
	close(fd);
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			return (unlink(".here_doc"), exit (1), 1);
		if (ft_strstr(line, av[2]))
		{
			free(line);
			break ;
		}
		write(1, line, sp_strlen(line));
		free(line);
	}
	return (0);
}

int	here_doc(char **av)
{
	int	doc;
	int	id;

	doc = open(".here_doc", O_CREAT | O_RDWR | O_APPEND, 0777);
	if (doc == -1)
		return (exit(1), 1);
	id = fork();
	if (id == -1)
		return (perror("fork "), close(doc), unlink(".here_doc"), exit(1), 1);
	if (id == 0)
	{
		read_from_heredoc(av, doc);
		exit (0);
	}
	wait(NULL);
	return (close(doc), 0);
}

int	first_cmd_heredoc(char **av, char **env, int *fd)
{
	int		doc;
	int		id;
	int		p_index;

	id = fork();
	if (id == 0)
	{
		doc = open(".here_doc", O_RDONLY);
		if (doc == -1)
			return (perror(".here_doc"),close(fd[1]), close(fd[0]), exit(1), 1);
		dup2(doc, 0);			
		close(doc);
		p_index = get_index_of_path(env);
		nrml_cmd(av[3], env, fd, p_index);
	}
	wait(NULL);
	close_fd_parent(fd);		
	return (0);
}
