/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrich <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:05:15 by okrich            #+#    #+#             */
/*   Updated: 2023/01/11 18:39:10 by okrich           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	counter(int n)
{
	int	i;

	i = 0;
	if (n < 1)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = counter(n);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[0] = '-';
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n > 0)
		n *= -1;
	while (n)
	{
		str[--len] = -(n % 10) + '0';
		n = n / 10;
	}
	return (str);
}

char	*generate_file(void)
{
	int		i;
	char	*num;
	char	*file;

	i = 0;
	while (1)
	{
		num = ft_itoa(i++);
		if (num == NULL)
			exit(1);
		file = ft_strjoin("/tmp/.here_doc", num, '0');
		free(num);
		if (file == NULL)
			exit(1);
		if (access(file, F_OK) == -1)
			return (file);
		free(file);
	}
	return (NULL);
}
