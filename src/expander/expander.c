/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:15:29 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/25 12:29:34 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

static void	expand_string_helper(
	char *str, size_t *i, char **line, t_env_list *list)
{
	if (str[*i] == '\\')
		*i = expand_backslash(str, *i, line);
	else if (str[*i] == '\'')
		*i = expand_single_quotes(str, *i, line);
	else if (str[*i] == '"')
		*i = expand_double_quotes(str, *i, line, list);
	else if (str[*i] == '$')
		*i = expand_dollar_sign(str, *i, line, list);
	else
		*i = expand_plain_text(str, *i, line);
}

static char	*expand_string(char *str, t_env_list *list)
{
	char	**result;
	char	*line;
	size_t	curr_index;
	size_t	i;

	curr_index = 0;
	result = (char **)ft_calloc(ft_strlen(str) + 1, sizeof(char *));
	i = 0;
	while (str[i])
	{
		line = NULL;
		expand_string_helper(str, &i, &line, list);
		if (line)
		{
			result[curr_index++] = ft_strdup(line);
			free(line);
		}
	}
	return (strings_join(result));
}

static char	**expand_all_strings(char **strs, t_env_list *list)
{
	char	**result;
	size_t	curr_string;
	size_t	index;

	if (!strs)
		return (NULL);
	result = (char **)ft_calloc(100, sizeof(char *));
	if (!result)
		return (NULL);
	index = 0;
	curr_string = 0;
	while (strs[curr_string])
		result[index++] = expand_string(strs[curr_string++], list);
	return (result);
}

static void	expand(t_command *cmd, t_env_list *list)
{
	char	**expanded;

	if (!cmd->str)
		return ;
	expanded = NULL;
	expanded = expand_all_strings(cmd->str, list);
	if (expanded != NULL)
	{
		free_strs(cmd->str);
		cmd->str = expanded;
	}
}

int	expander(t_app *app)
{
	t_command	*cmd;

	cmd = app->commands_list;
	if (!cmd)
		return (EXIT_SUCCESS);
	while (cmd)
	{
		expand(cmd, app->env_list);
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
