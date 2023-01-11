/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:40:01 by okrich            #+#    #+#             */
/*   Updated: 2023/01/11 11:43:05 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_doc(void)
{
	int	fd;

	fd = open(".here_doc", O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd == -1)
		return (exit(1), 1);
	return (fd);
}

int	ft_heredoc(char **av, char **env)
{
	int	doc;
	int	fd[2];
	int	id;

	doc = get_doc();
	read_from_heredoc(av[0], doc);
	if (pipe(fd) == -1)
		return (perror("pipe "), exit (1), 1);
	first_cmd_heredoc(av[1], env, fd);
	return (0);	
}

int	read_from_heredoc(char *limiter, int fd)
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
		if (ft_strstr(line, limiter))
		{
			free(line);
			break ;
		}
		write(1, line, sp_strlen(line));
		free(line);
	}
	return (0);
}

int	first_cmd_heredoc(char *cmd, char **env, int *fd)
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
		nrml_cmd(cmd, env, fd, p_index);
	}
	wait(NULL);
	close_fd_parent(fd);		
	return (0);
}
