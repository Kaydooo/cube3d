/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 07:27:39 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/14 17:17:51 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
int		ft_strlen_gnl(char *str);
char	*ft_strjoin_gnl(char *str1, char	*str2);
char	*ft_substr_gnl(char *str, int start, int len);
char	*ft_strchr_gnl(char *s, char c);
char	*ft_strdup_gnl(char *src);

#endif