/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:08:50 by okrich            #+#    #+#             */
/*   Updated: 2023/01/05 21:41:38 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_index_of_path(char **env)
{
	int	p_index;

	p_index = 0;
	while(env[p_index])
	{
		if (ft_strstr(env[p_index], "PATH"))
			break ;
		p_index++;
	}
	if (env[p_index] == NULL)
	{
		//TODO: print error
		exit(1);
	}
	
	return (p_index);
}

void	child_proccess1(char **av, char **env, int *fd, int infile)
{
	char	**arg;
	char	*path;
	int		p_index;

	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	dup2(infile, 0);
	close(infile);
	p_index = get_index_of_path(env);
	arg = ft_split(av[2], ' ');
	path = get_path(arg[0], env[p_index]);
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

void	child_proccess2(char **av, char **env, int *fd, int outfile)
{
	char	**arg;
	char	*path;
	int		p_index;

	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(outfile, 1);
	close(outfile);
	p_index = get_index_of_path(env);
	arg = ft_split(av[3] , ' ');
	path = get_path(arg[0], env[p_index]);
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
	int		p_index;

	//FIX: check if env == NULL || path is not in env
	if (ac != 5 || env == NULL)
		return (0);
	get_in_out_file(&infile, &outfile, av[1], av[4]);
	pipe(fd);
	id = fork();
	if (id == 0)
		child_proccess1(av, env, fd, infile);
	id2 = fork();
	if (id2 != 0)
		child_proccess2(av, env, fd, outfile);
	wait(NULL);
}
