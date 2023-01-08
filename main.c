/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:08:50 by okrich            #+#    #+#             */
/*   Updated: 2023/01/08 10:51:08 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	child_proccess1(char **av, char **env, int	*fd, int p_index)
{
	char	*path;
	char	**arg;
	int		infile;

	close (fd[0]);
	infile = open(av[1], O_RDWR);
	if (infile == -1)
		return (perror(av[1]), close(fd[1]), 1);
	if (dup2(fd[1], 1) == -1)
		return (perror("dup2 "), close(fd[1]), close(infile), 1);
	close(fd[1]);
	if (dup2(infile, 0) == -1)
		return (perror("child1 dup2 "), close(infile), 1);
	close(infile);
	arg = ft_split(av[2], ' ');
	if (arg == NULL)
		return (1);
	execve(arg[0], arg, env);
	path = get_path(arg[0], env[p_index]);
	if (path == NULL)
		return (free_words(arg), 1);
	if (execve(path, arg, env) == -1)
		return (perror("execve "), free_words(arg), free(path), 1);
	return (0);
}

int	child_proccess2(char **av, char **env, int *fd, int p_index)
{
	char	*path;
	char	**arg;
	int		outfile;

	close (fd[1]);
	outfile = open(av[4], O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (outfile == -1)
		return (perror(av[4]), close(fd[0]), 1);
	if (dup2(fd[0], 0) == -1)
		return (perror("dup2 "), close(fd[0]), close(outfile), 1);
	close(fd[0]);
	if (dup2(outfile, 1) == -1)
		return (perror("child2 dup2 "), close(outfile), 1);
	close(outfile);
	arg = ft_split(av[3], ' ');
	if (arg == NULL)
		return (1);
	execve(arg[0], arg, env);	
	path = get_path(arg[0], env[p_index]);
	if (path == NULL)
		return (free_words(arg), 1);
	if (execve(path, arg, env) == -1)
		return (perror("execve "), free_words(arg), free(path), 1);
	return (0);
}

int	ft_pipex(char **av, char **env, int p_index)
{
	int	child1;
	int	child2;
	int	fd[2];

	if (pipe(fd) == -1)
		return (perror("pipe "), 1);
	child1 = fork();
	if (child1 == -1)
		return (perror("fork "), 1);
	if (child1 == 0)
		if (child_proccess1(av, env, fd, p_index))
			exit (1);
	child2 = fork();
	if (child2 == -1)
		return (perror("fork "), 1);
	if (child2 == 0)
		if (child_proccess2(av, env, fd, p_index))
			exit(1);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int	p_index;

	// chech env and in and cmd1 cmd2 out
	if (ac != 5 || env == NULL)
		return (1);
	p_index = get_index_of_path(env);
	if (p_index == -1)
		return (write(2, "path not found\n", 15), 1);
	ft_pipex(av, env, p_index);
	return (0);
}
