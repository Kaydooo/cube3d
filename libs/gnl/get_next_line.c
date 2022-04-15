/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 07:27:18 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/14 17:27:13 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **s)
{
	free(*s);
	*s = NULL;
}

char	*ft_line(char	**s, int i)
{
	char	*temp;
	char	*ret;

	if (ft_strchr_gnl(*s, '\n'))
	{
		temp = *s;
		ret = ft_substr_gnl(*s, 0, i);
		*s = ft_strdup_gnl(temp + i);
		free(temp);
		temp = NULL;
		return (ret);
	}
	else if (*s)
	{
		temp = ft_strdup_gnl(*s);
		free(*s);
		*s = NULL;
		return (temp);
	}
	return (NULL);
}

int	nl_index(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

int	ft_reader(char **save, int fd, int n)
{
	char	*temp;
	char	buff[BUFFER_SIZE + 1];

	while (n && !ft_strchr_gnl(*save, '\n'))
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n <= 0)
			break ;
		buff[n] = '\0';
		temp = *save;
		*save = ft_strjoin_gnl(temp, buff);
		free(temp);
		temp = NULL;
	}
	return (n);
}

char	*get_next_line(int fd)
{
	static char	*save[8192];
	int			index;
	int			b;

	b = 1;
	if (fd < 0 || fd > 8192 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!save[fd])
		save[fd] = ft_strdup_gnl("");
	b = ft_reader(&save[fd], fd, b);
	if (*save[fd] == '\0' && b <= 0)
	{
		
		free(save[fd]);
		save[fd] = NULL;
		return (NULL);
	}
	index = nl_index(save[fd]);
	return (ft_line(&save[fd], index + 1));
}
