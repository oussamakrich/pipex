/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:08:40 by okrich            #+#    #+#             */
/*   Updated: 2023/01/08 22:27:03 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <sys/fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>



int		sp_strlen(char *str);
int		sp_strlcpy(char *dst, char *src, int dstsize);
char	**ft_split(char *s, char c);
void	free_words(char **words);

char	*ft_strjoin(char *s1, char *s2);
char	*ft_strcpy(char *dst, char *src);


char	*skip(char *s, char c);
int	ft_strstr(char *str, char *to_find);
char	*get_path(char *cmd, char *path);


void	get_in_out_file(int *in, int *out, char *file_in, char *file_out);
int	get_index_of_path(char **env);

//--------------------------------------

int	first_cmd(char **av, char **env, int *fd, int p_index);
int	last_cmd(char *av, char **env, char *out);
int	nrml_cmd(char *av, char **env, int *fd, int p_index);
void	close_fd(int *fd);

#endif
