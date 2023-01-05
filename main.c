/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:08:50 by okrich            #+#    #+#             */
/*   Updated: 2023/01/05 21:27:07 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>

void	child_proccess1(char **av, char **env, int *fd, int p_indice, int infile)
{
	char	**arg;
	char	*path;

	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	dup2(infile, 0);
	close(infile);
	arg = ft_split(av[2], ' ');
	path = get_path(arg[0], env[p_indice]);
	if (path == NULL)
	{
		write(2, "command not found : ", 20);
		write(2, arg[0], sp_strlen(arg[0]));
		exit (1);
	}
	execve(path, arg, env);
	{
		perror("execve ");
		exit(1);
	}
}

void	child_proccess2(char **av, char **env, int *fd, int p_indice, int outfile)
{
	char	**arg;
	char	*path;

	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(outfile, 1);
	close(outfile);
	arg = ft_split(av[3] , ' ');
	path = get_path(arg[0], env[p_indice]);
	if (path == NULL)
	{
		write(2, "command not found : ", 20);
		write(2, arg[0], sp_strlen(arg[0]));
		exit (1);
	}
	if (execve(path, arg, env) == -1)
	{
		perror("execve ");
		exit(1);
	}
}

void	get_in_out_file(int *in, int *out, char *file_in, char *file_out)
{	
	*in = open(file_in, O_RDWR);
	*out = open(file_out, O_CREAT | O_RDWR, 0777);
	if (*in == -1 || *out == -1)
	{
		perror("error ");
		exit (1);
	}
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	int		id;
	int		id2;
	int		outfile;
	int		infile;
	int		p_indice;

	//FIX: check if env == NULL || path is not in env
	if (ac != 5 || env == NULL)
		return (0);
	get_in_out_file(&infile, &outfile, av[1], av[4]);
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
		child_proccess1(av, env, fd, p_indice, infile);
	id2 = fork();
	if (id2 != 0)
		child_proccess2(av, env, fd, p_indice, outfile);
	wait(NULL);
}
