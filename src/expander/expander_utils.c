/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:15:29 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/25 12:10:32 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

void	free_strs(char **strs)
{
	size_t	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

bool	is_var_name(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9') || (c == '_'))
		return (true);
	return (false);
}

char	*strings_join(char **strs)
{
	char	*result;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (strs[i])
		count += ft_strlen(strs[i++]);
	result = (char *)ft_calloc(count + 1, sizeof(char));
	count = 0;
	i = 0;
	while (strs[count])
	{
		ft_memcpy(result + i, strs[count], ft_strlen(strs[count]));
		i += ft_strlen(strs[count]);
		free(strs[count]);
		count++;
	}
	free(strs);
	return (result);
}
