/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 10:52:10 by okrich            #+#    #+#             */
/*   Updated: 2023/01/10 19:25:52 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	my_pipe(char **av, char **env, int *fd, int i)
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
	{
		if (i == 2)
			first_cmd(av, env, fd, p_index);
		else
			nrml_cmd(av[i], env, fd, p_index);
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

int	execute_cmd(int ac, char **av, char **env, int	flag)
{
	int	nb_cmd;
	int	fd[2];
	int	i;

	nb_cmd = ac - 3;
	i = 2;
	if (flag)
	{
		nb_cmd = ac - 4;
		i = 3;
	}
	while (nb_cmd > 1)
	{
		if (pipe(fd) == -1)
			return (perror("pipe "), 1);
		if (i == 3 && flag == 1)
		{
			first_cmd_heredoc(av, env, fd);
			close_fd_parent(fd);
			i++;
		}
		my_pipe(av, env, fd, i++);
		close_fd_parent(fd);
		nb_cmd--;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int	child;
	int	status;
	int	flag;

	if (ac < 5)
		return (1);
	flag = 0;
	if (ft_strstr(av[1], "here_doc\0"))
	{
		flag = 1;
		here_doc(av);
	}
	execute_cmd(ac, av, env, flag);
	while (wait(NULL) != -1);
	child = fork();	
	if (child == -1)
		return (perror("fork "), 1);
	if (child == 0)
		last_cmd(av[ac - 2], env, av[ac - 1]);	
	waitpid(child, &status, 0);
	return (WEXITSTATUS(status));
}
