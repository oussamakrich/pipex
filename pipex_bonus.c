/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 10:52:10 by okrich            #+#    #+#             */
/*   Updated: 2023/01/11 18:52:17 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	my_pipe(char *cmd, char **env, int *fd)
{
	int	child;
	int	p_index;

	p_index = get_index_of_path(env);
	child = fork();
	if (child == -1)
	{
		close(fd[0]);
		close(fd[1]);
		perror("fork ");
		exit(1);
	}
	if (child == 0)
	{
		nrml_cmd(cmd, env, fd, p_index);
		exit(1);
	}
}

int	close_fd_parent(int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], 0) == -1)
		return (close(fd[0]), exit(1), 1);
	close(fd[0]);
	return (0);
}

int	ft_pipe(char **av, int ac, char **env)
{
	int	nb_cmd;
	int	fd[2];
	int	i;

	nb_cmd = ac - 5;
	i = 3;
	if (ft_strcmp(av[1], "here_doc", '0') == 0)
	{
		i = 4;
		nb_cmd = ac - 6;
	}
	while (nb_cmd--)
	{
		if (pipe(fd) == -1)
			return (perror("pipe "), 1);
		my_pipe(av[i], env, fd);
		i++;
		close_fd_parent(fd);
	}
	while (wait(NULL) != -1)
		;
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*doc;

	if (ac < 5)
		return (1);
	get_index_of_path(env);
	if (ft_strcmp(av[1], "here_doc", '0') == 0)
	{
		doc = generate_file();
		ft_heredoc(av + 2, env, doc);
		unlink(doc);
		free(doc);
	}
	else
		exec_first_cmd(av, env);
	ft_pipe(av, ac, env);
	return (exec_last_cmd(av, ac, env));
}
