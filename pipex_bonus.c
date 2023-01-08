/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 10:52:10 by okrich            #+#    #+#             */
/*   Updated: 2023/01/08 22:43:18 by okrich           ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	int	nb_cmd;
	int	fd[2];
	int	child;
	int	i;

	if (ac < 5 || env == NULL)
		return (1);
	nb_cmd = ac - 3;
	i = 2;
	while (nb_cmd > 1)
	{
		pipe(fd);
		my_pipe(av, env, fd, i++);
		nb_cmd--;
	}
	while(wait(NULL) != -1);
	child = fork();	
	if (child == -1)
		return (perror("fork "), 1);
	if (child == 0)
		last_cmd(av[ac - 2], env, av[ac - 1]);	
	wait(NULL);
}
