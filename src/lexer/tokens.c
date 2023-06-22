/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:54:30 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/05 21:21:25 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token_type	is_token(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (GREAT);
	else if (c == '<')
		return (LESS);
	return (0);
}

int	handle_token(char *str, int start, t_lexer_token **list)
{
	t_token_type	token_type;

	token_type = is_token(str[start]);
	if (token_type == GREAT && is_token(str[start + 1]) == GREAT)
	{
		if (!add_node(NULL, G_GREAT, list))
			return (-1);
		return (start + 2);
	}
	else if (token_type == LESS && is_token(str[start + 1]) == LESS)
	{
		if (!add_node(NULL, L_LESS, list))
			return (-1);
		return (start + 2);
	}
	else if (token_type)
	{
		if (!add_node(NULL, token_type, list))
			return (-1);
		return (start + 1);
	}
	return (0);
}

int	read_word(int start, char *str, t_lexer_token **list)
{
	int	i;

	i = start;
	while (str[i] && !(is_token(str[i])))
	{
		i = handle_quotes(i, str, '"');
		i = handle_quotes(i, str, '\'');
		if (ft_iswhitespace(str[i]))
			break ;
		if (str[i] != '\0' && str[i] != '"' && str[i] != '\'')
			i++;
	}
	if (!add_node(ft_substr(str, start, i - start), 0, list))
		return (-1);
	return (i);
}

int	get_tokens(t_app *app)
{
	int	i;

	i = 0;
	while (app->input[i])
	{
		while (ft_iswhitespace(app->input[i]))
			i++;
		if (is_token(app->input[i]))
			i = handle_token(app->input, i, &app->lexer_tokens);
		else
			i = read_word(i, app->input, &app->lexer_tokens);
		if (i < 0)
			return (0);
	}
	return (1);
}
