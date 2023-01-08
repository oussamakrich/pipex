/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 10:52:10 by okrich            #+#    #+#             */
/*   Updated: 2023/01/08 19:05:20 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int	child_proccess(char *av, char **env, int p_index, int *fd)
{
	char	**arg;
	char	*path;

	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	arg = ft_split(av, ' ');
	execve(arg[0], arg, env);
	path = get_path(arg[0], env[p_index]);
	if (path == NULL)
		return (free_words(arg), 1);
	if (execve(path, arg, env) == -1)
		return (free(path), free_words(arg), 1);
	return (0);
}



int	main(int ac, char **av, char **env)
{
	int	nb_cmd;
	int	child1;
	int	p_index;
	int	fd[2];
	int	i;

	if (ac < 5)
		return (1);	
	p_index = get_index_of_path(env);
	if (p_index == -1)
		return (1);
	nb_cmd = ac - 3;
	i = 2;
	while (nb_cmd--)
	{
		pipe(fd);
		child1 = fork();
		if (child1 == 0)
		{
			if (i == 2)
			{
				printf("i == 2\n");
				first_cmd(av[i], env, p_index, fd, av);
			}
			else if (i == ac - 2)
			{
				printf("i == ac - 2\n");
				last_cmd(av[i], env, p_index, fd, av[ac - 1]);
			}
			else
			{
				printf("i == 3adi\n");
				child_proccess(av[i], env, p_index, fd);
			}
			exit(1);
		}
		dup2(fd[0], 0);
		close(fd[0]);	
		close(fd[1]);	
		i++;
	}
}
