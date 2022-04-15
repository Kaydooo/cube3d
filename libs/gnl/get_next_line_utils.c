/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 07:27:33 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/14 17:28:45 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_gnl(char *s, char c)
{

	char *str = s;
	while(*str != '\0')
	{
		if(*str == c)
			return str;
		str++;
	}
	return 0;

}
int	ft_strlen_gnl(char *str)
{
	int i = 0 ;
	if(!str)
		return (0);
	while(str[i])
	{
		i++;
	}
		
		return i;
}

char	*ft_strjoin_gnl(char *str1, char	*str2)
{

	char *res = malloc(sizeof(char) * ft_strlen_gnl(str1) + ft_strlen_gnl(str2) + 1);
	int i = 0;
	int k = 0;
	while(str1[i])
		res[k++] = str1[i++];	
	i = 0;
	
	while(str2[i])
		res[k++] = str2[i++];
	
	res[k] = '\0';
	
	return res;



}
char	*ft_substr_gnl(char *str, int start, int len)
{


	int i = 0;
	char *res = malloc(sizeof(char) * (len + 1));
	
	while(str[start] && i < len)
		res[i++] = str[start++];
	res[i] = '\0';
	return res;
}

char	*ft_strdup_gnl(char *src)
{
	char	*dest;
	size_t	z;
	size_t	i;

	z = ft_strlen_gnl(src);
	dest = malloc(sizeof(char) * (z + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i != (z + 1))
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}