/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 10:52:10 by okrich            #+#    #+#             */
/*   Updated: 2023/01/11 11:52:39 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	my_pipe(char *cmd, char **env, int *fd)
{
	int	child;
	int	p_index;

	p_index = get_index_of_path(env);
	if (p_index == -1)
		exit(1);
	child = fork();
	if (child == -1)
		exit(1);
	if (child == 0)
		nrml_cmd(cmd, env, fd, p_index);
}

int	close_fd_parent(int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], 0) == -1)
		return (close(fd[0]), exit(1), 1);
	close(fd[0]);
	return (0);
}

int	exec_first_cmd(char **av, char **env)
{
	int	id;
	int	fd[2];
	int	p_index;

	p_index = get_index_of_path(env);
	if (p_index == -1)
		return (exit(1), 1);
	if (pipe(fd) == -1)
		return (perror("pipe "), exit(1), 0);	
	id = fork();
	if (id == -1)
		return (perror("fork "), close(fd[0]), close(fd[1]), exit(1), 1);
	if (id == 0)
	{
		first_cmd(av, env, fd, p_index);
		exit(1);
	}
	close_fd_parent(fd);
	wait(NULL);
	return (0);
}

int	ft_pipe(char **av, int ac, char **env)
{
	int	nb_cmd;
	int	fd[2];
	int	i;

	nb_cmd = ac - 5;
	i = 3;
	if (ft_strstr(av[1], "here_doc\0"))
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
	while (wait(NULL) != -1);
	return (0);
}

int	exec_last_cmd(char **av, int ac, char **env)
{
	int	child;
	int	status;

	child = fork();	
	if (child == -1)
		return (perror("fork "), 1);
	if (child == 0)
		last_cmd(av[ac - 2], env, av[ac - 1]);	
	waitpid(child, &status, 0);
	return (WEXITSTATUS(status));
}

int	main(int ac, char **av, char **env)
{
	if (ac < 5)
		return (1);
	if (ft_strstr(av[1], "here_doc\0"))
	{
		ft_heredoc(av + 2, env);
		unlink(".here_doc");
	}
	else
		exec_first_cmd(av, env);
	ft_pipe(av, ac, env);
	return (exec_last_cmd(av, ac, env));
}
