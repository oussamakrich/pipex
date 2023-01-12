/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:08:40 by okrich            #+#    #+#             */
/*   Updated: 2023/01/11 19:30:54 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <sys/_types/_ssize_t.h>
# include <sys/fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define BUFFER_SIZE 5

ssize_t	ft_strlen(char *str);
char	**ft_split(char *s, char c);
void	free_words(char **words);

char	*ft_strjoin(char *s1, char *s2, char c);
char	*ft_strcpy(char *dst, char *src);

char	*skip(char *s, char c);
int		ft_strstr(char *str, char *to_find);
char	*get_path(char *cmd, char *path);
int		ft_strcmp(char *s1, char *s2, char c);

int		get_index_of_path(char **env);

int		exec_first_cmd(char **av, char **env);
int		first_cmd(char **av, char **env, int *fd, int p_index);
int		exec_last_cmd(char **av, int ac, char **env);
int		last_cmd(char *av, char **env, char *out);
int		nrml_cmd(char *av, char **env, int *fd, int p_index);

int		close_fd_parent(int *fd);

char	*get_strnjoin(char *s1, char *s2, ssize_t i);
char	*ft_strndup(char *s1, ssize_t n, ssize_t	*fail);
char	*get_next_line(int fd);
char	*ft_strncpy(char *dst, char *src, ssize_t dstsize);

int		first_cmd_heredoc(char *cmd, char **env, int *fd, char *file);
int		write_in_heredoc(char *limiter, int fd, char *file);

void	my_pipe(char *cmd, char **env, int *fd);

char	*generate_file(void);
int		ft_heredoc(char **av, char **env, char *file);

#endif
