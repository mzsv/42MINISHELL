/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:32:14 by amenses-          #+#    #+#             */
/*   Updated: 2022/11/24 07:01:57 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_findchr(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	size_t	i;
	size_t	s1_len;
	char	*s;

	if (!s1)
		s1_len = 0;
	else
		s1_len = ft_findchr(s1, '\0');
	s = (char *)malloc((s1_len + ft_findchr(s2, '\0') + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		s[i] = s1[i];
		i++;
	}
	while (i < s1_len + ft_findchr(s2, '\0'))
	{
		s[i] = s2[i - s1_len];
		i++;
	}
	s[i] = '\0';
	free(s1);
	return (s);
}

char	*ft_substrfree(char *s, unsigned int start, size_t len, int f)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	if (start > i)
		len = 0;
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	if (f)
		free(s);
	return (sub);
}

char	*ft_getl(char *pocket, ssize_t	*n)
{
	char	*l;

	l = NULL;
	if (((!pocket || !ft_findchr(pocket, '\0')) && *n == 0))
		return (NULL);
	if (ft_findchr(pocket, '\n') < ft_findchr(pocket, '\0') || *n == 0)
	{
		l = ft_substrfree(pocket, 0, ft_findchr(pocket, '\n') + 1, 0);
		if (!l)
			return (NULL);
	}
	return (l);
}

char	*ft_fillpocket(char *pocket, ssize_t *n)
{
	size_t			len;
	unsigned int	start;

	if (!pocket)
		return (NULL);
	start = ft_findchr(pocket, '\n') + 1;
	len = ft_findchr(pocket, '\0') - ft_findchr(pocket, '\n') - 1;
	if (ft_findchr(pocket, '\n') < ft_findchr(pocket, '\0'))
	{
		pocket = ft_substrfree(pocket, start, len, 1);
		if (!pocket)
			return (NULL);
		*n = 0;
	}
	else if (*n <= 0)
	{
		free(pocket);
		pocket = NULL;
	}
	return (pocket);
}
