/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:13:01 by okrich            #+#    #+#             */
/*   Updated: 2023/01/07 13:33:51 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strstr(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && to_find[i] == str[i])
		i++;
	if (to_find[i] == '\0')
		return (1);
	return (0);
}

int	get_index_of_path(char **env)
{
	int	p_index;

	p_index = 0;
	while (env[p_index])
	{
		if (ft_strstr(env[p_index], "PATH"))
			return (p_index);
		p_index++;
	}
	return (-1);
}

char	*get_path(char *cmd, char *path)
{
	char	*res;
	char	**all_path;
	int		i;

	path = path + 5;
	all_path = ft_split(path, ':');
	if (all_path == NULL)
		return (NULL);
	i = 0;
	while (all_path[i])
	{
		res = ft_strjoin(all_path[i], cmd);
		if (res == NULL)
			return (free_words(all_path), NULL);
		if (access(res, F_OK) == 0)
			return (free_words(all_path), res);
		i++;
		free(res);
	}
	perror(cmd);
	return (free_words(all_path), NULL);
}
