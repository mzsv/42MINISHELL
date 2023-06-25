/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:04:58 by alexmitcul        #+#    #+#             */
/*   Updated: 2023/06/25 12:35:45 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * - Description:
 * Allocates (with malloc(3)) and returns a copy of 's1' with the characters
 * specified in 'set' removed from the beginning and the end of the string.
 *
 * - Parameters:
 * s1: The string to be trimmed.
 * set:	the reference set of characters to trim.
 *
 * - Return value:
 * The trimmed string.
 * NULL if the allocation fails.
**/

#include "libft.h"

static int	ft_isspace(char ch, const char *set)
{
	while (*set != '\0')
	{
		if (ch == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *str, const char *set)
{
	size_t		trimmed_length;
	char		*trimmed_str;
	const char	*start;
	const char	*end;

	if (str == NULL)
		return (NULL);
	start = str;
	end = str + ft_strlen(str) - 1;
	while (*start != '\0' && ft_isspace(*start, set))
		start++;
	while (end > start && ft_isspace(*end, set))
		end--;
	trimmed_length = end - start + 1;
	trimmed_str = malloc(trimmed_length + 1);
	if (trimmed_str != NULL)
	{
		ft_memcpy(trimmed_str, start, trimmed_length);
		trimmed_str[trimmed_length] = '\0';
	}
	return (trimmed_str);
}
