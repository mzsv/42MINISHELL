/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:15:29 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/25 12:20:11 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

static bool	is_valid_to_expand_from_double_quotes(const char *str, size_t i)
{
	if (str[i] == '\\' && str[i + 1] && str[i + 1] == '"')
		return (true);
	if (str[i] == '\\' && str[i + 1] && str[i + 1] == '$')
		return (true);
	if (str[i] == '\\' && str[i + 1] && str[i + 1] == '\\')
		return (true);
	return (false);
}

static size_t	expand_double_quotes_helper(
	char *str, size_t i, char **tmp, t_env_list *list)
{
	if (is_valid_to_expand_from_double_quotes(str, i))
		i = expand_backslash(str, i, tmp);
	else if (str[i] == '$')
		i = expand_dollar_sign(str, i, tmp, list);
	else
		i = expand_plain_text(str, i, tmp);
	return (i);
}

size_t	expand_double_quotes(char *str, size_t start, char **line,
		t_env_list *list)
{
	char	**result;
	char	*tmp;
	size_t	curr_index;
	size_t	i;

	result = (char **)ft_calloc(ft_strlen(str) + 1, sizeof(char *));
	curr_index = 0;
	i = start + 1;
	while (str[i] && str[i] != '"')
	{
		tmp = NULL;
		i = expand_double_quotes_helper(str, i, &tmp, list);
		if (tmp)
		{
			result[curr_index++] = ft_strdup(tmp);
			free(tmp);
		}
	}
	*line = strings_join(result);
	if (str[i] == '"')
		return (i + 1);
	return (i);
}
