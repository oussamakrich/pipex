/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_boonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:49:22 by okrich            #+#    #+#             */
/*   Updated: 2023/01/08 22:43:36 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>

int	first_cmd(char **av, char **env, int *fd, int p_index)
{
	char	**arg;
	char	*path;
	int		infile;
	
	close(fd[0]);
	infile = open(av[1], O_RDWR);
	if (infile == -1)
		return (perror(arg[1]), close(fd[1]), 1);
	if (dup2(infile, 0) == -1 || dup2(fd[1], 1) == -1)
		return (close(infile), close(fd[1]), perror("dup2 "), 1);
	close(infile);
	close(fd[1]);
	arg = ft_split(av[2], ' ');
	if (arg == NULL)
		return (1);
	execve(arg[0], arg, env);		
	path = get_path(arg[0], env[p_index]);
	if (path == NULL)
		return (free_words(arg), 1);
	if (execve(path, arg, env) == -1)
		return (free_words(arg), free(path), perror("execve "), 1);
	return (0);
}

int	nrml_cmd(char *av, char **env, int *fd, int p_index)
{
	char	**arg;
	char	*path;

	close(fd[0]);
	if (dup2(fd[1], 1) == -1)
		return (close(fd[1]), perror("dup2 "), 1);
	close(fd[1]);
	arg = ft_split(av, ' ');
	if (arg == NULL)
		return (1);
	execve(arg[0], arg, env);	
	path = get_path(arg[0], env[p_index]);
	if (path == NULL)
		return (free_words(arg), 1);
	if (execve(path, arg, env) == -1)
		return (free_words(arg), free(path), perror("execve "), 1);
	return (0);
}

int	last_cmd(char *av, char **env, char *out)
{
	char	**arg;
	char 	*path;
	int		outfile;
	int		p_index;

	p_index = get_index_of_path(env);
	if (p_index == -1)
		return (exit(1), 1);
	outfile = open(out, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (outfile == -1)
		return (perror(out), 1);
	if (dup2(outfile, 1) == -1)
		return (close(outfile), perror("dup2 "), 1);
	close(outfile);
	arg = ft_split(av, ' ');
	if (arg == NULL)
		return (1);
	execve(arg[0], arg, env);
	path = get_path(arg[0], env[p_index]);
	if (path == NULL)
		return (free_words(arg), 1);
	if (execve(path, arg, env) == -1)
		return (free(path), free_words(arg), 1);
	return (0);
}
