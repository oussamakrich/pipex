/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:08:40 by okrich            #+#    #+#             */
/*   Updated: 2023/01/05 17:13:59 by okrich           ###   ########.fr       */
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

char	*ft_strnjoin(char *s1, char *s2);
char	*ft_strcpy(char *dst, char *src);


int	ft_strstr(char *str, char *to_find);
char	*get_path(char *cmd, char *path);

#endif
