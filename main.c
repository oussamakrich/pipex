/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:08:50 by okrich            #+#    #+#             */
/*   Updated: 2023/01/05 19:55:15 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>

void	child_proccess1(char **av, char **env, int *fd, int p_indice)
{
	char	**arg;
	char	*path;
	int		infile;

	infile = open(av[1], O_RDWR);
	if (infile == -1)
	{
		perror("error");
		exit(1);
	}
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	dup2(infile, 0);
	close(infile);
	arg = ft_split(av[2], ' ');
	path = get_path(arg[0], env[p_indice]);
	execve(path, arg, env);
}

void	child_proccess2(char **av, char **env, int *fd, int p_indice)
{
	char	**arg;
	char	*path;
	int		outfile;

	outfile = open(av[4], O_CREAT | O_RDWR, 0777);
	if (outfile == -1)
	{
		perror("error ");
		exit(1);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(outfile, 1);
	close(outfile);
	arg = ft_split(av[3] , ' ');
	path = get_path(arg[0], env[p_indice]);
	execve(path, arg, env);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	int		id;
	int		id2;
	int		outfile;
	int		p_indice;

	//FIX: check if env == NULL || path is not in env
	if (ac != 5 || env == NULL)
		return (0);
	p_indice = 0;
	while(env[p_indice])
	{
		if (ft_strstr(env[p_indice], "PATH"))
			break ;
		p_indice++;
	}
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		child_proccess1(av, env, fd, p_indice);
	}
	if (id != 0)
		id2 = fork();
	if (id2 != 0)
	{
		child_proccess2(av, env, fd, p_indice);
	}
	wait(NULL);
}
