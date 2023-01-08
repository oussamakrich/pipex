/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_boonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:49:22 by okrich            #+#    #+#             */
/*   Updated: 2023/01/08 19:08:07 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_cmd(char *av, char **env, int p_index, int *fd,char **argv)
{
	char	*path;
	char	**arg;
	int		infile;

	close (fd[0]);
	infile = open(argv[1], O_RDWR);
	if (infile == -1)
		return (perror("in file "), close(fd[1]), 1);
	if (dup2(fd[1], 1) == -1)
		return (perror("dup2 "), close(fd[1]), close(infile), 1);
	close(fd[1]);
	if (dup2(infile, 0) == -1)
		return (perror("dup2 "), close(infile), 1);
	close(infile);
	arg = ft_split(av, ' ');
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


int	last_cmd(char *av, char **env, int p_index, int *fd, char *out)
{
	char	*path;
	char	**arg;
	int		outfile;

	close(fd[1]);
	close(fd[0]);
	outfile = open(out, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (outfile == -1)
		return (perror(out), 1);
	if (dup2(outfile, 1) == -1)
		return (perror("dup2 "), close(outfile), 1);
	close(outfile);
	arg = ft_split(av, ' ');
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
