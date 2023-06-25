/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 10:51:57 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/25 12:33:02 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

extern int	g_exit_status;

static int	expand_dollar_sign_helper(
	char *str, size_t start, size_t end, char **result)
{
	char	*tmp;

	if (str[end] == '\0')
	{
		*result = ft_strdup("$");
		return (start + 1);
	}
	if (str[end] && str[end] == '?')
	{
		*result = ft_itoa(g_exit_status);
		return (start + 2);
	}
	if (str[end] && is_var_name(str[end]) == false)
	{
		tmp = ft_substr(str, start, 2);
		*result = tmp;
		return (end + 1);
	}
	return (-1);
}

size_t	expand_dollar_sign(char *str, size_t start, char **line,
		t_env_list *list)
{
	size_t	end;
	int		index;
	char	*key;
	char	*result;

	end = start + 1;
	index = expand_dollar_sign_helper(str, start, end, line);
	if (index >= 0)
		return (index);
	while (str[end] && is_var_name(str[end]))
		end++;
	key = ft_substr(str, start + 1, end - start - 1);
	result = get_env_value(list, key);
	if (result)
		result = ft_strdup(result);
	free(key);
	*line = result;
	return (end);
}

size_t	expand_single_quotes(char *str, size_t start, char **line)
{
	size_t	end;
	size_t	i;
	char	*result;

	end = start + 1;
	while (str[end] && str[end] != '\'')
		end++;
	result = (char *)ft_calloc(end - start, sizeof(char));
	start++;
	i = 0;
	while (str[start] && start < end)
		result[i++] = str[start++];
	*line = result;
	if (str[end] == '\0')
		return (end);
	return (end + 1);
}

size_t	expand_plain_text(const char *str, size_t start, char **line)
{
	char	*result;

	result = ft_calloc(2, sizeof(char));
	result[0] = str[start];
	*line = result;
	return (start + 1);
}

size_t	expand_backslash(const char *str, size_t start, char **line)
{
	char	*result;

	result = ft_calloc(2, sizeof(char));
	result[0] = str[start + 1];
	*line = result;
	return (start + 2);
}
