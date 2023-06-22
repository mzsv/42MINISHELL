/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:28:54 by amenses-          #+#    #+#             */
/*   Updated: 2022/11/24 06:32:28 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	ft_findchr(char *s, char c);
char	*ft_strjoinfree(char *s1, char *s2);
char	*ft_substrfree(char *s, unsigned int start, size_t len, int f);
char	*ft_getl(char *pocket, ssize_t	*n);
char	*ft_fillpocket(char *pocket, ssize_t *n);

#endif