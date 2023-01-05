/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:13:01 by okrich            #+#    #+#             */
/*   Updated: 2023/01/05 21:47:59 by okrich           ###   ########.fr       */
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

char	*ft_duplicate(char *str)
{
	char	*ret;
	int		len;
	int		i;

	i = 0;
	len = sp_strlen(str);
	ret = malloc(len);
	if (ret == NULL)
		return (NULL);
	ft_strcpy(ret, str);
	return (ret);
}

char	*get_path(char *cmd, char *path)
{
	char	*res;
	char	**all_path;
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(path, '=');
	all_path = ft_split(tmp[1], ':');
	free_words(tmp);
	while (all_path[i])
	{
		all_path[i] = ft_strnjoin(all_path[i], "/");
		all_path[i] = ft_strnjoin(all_path[i], cmd);
		if (access(all_path[i], F_OK) == 0)
			break ;
		i++;
	}
	if (all_path[i] == NULL)
		return (free_words(all_path), NULL);
	res = ft_duplicate(all_path[i]);
	free_words(all_path);
	return (res);
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
