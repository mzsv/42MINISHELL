/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:13:05 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/25 12:37:01 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	count_pipes(t_app *app)
{
	t_lexer_token	*tmp;

	tmp = app->lexer_tokens;
	app->pipes_count = 0;
	while (tmp)
	{
		if (tmp->token_type == PIPE)
			app->pipes_count += 1;
		tmp = tmp->next;
	}
}

t_parser	*init_parser(t_app *app)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	parser->app = app;
	parser->lexer_list = app->lexer_tokens;
	parser->redirs = NULL;
	parser->redirs_count = 0;
	return (parser);
}

int	parser(t_app *app)
{
	t_parser	*parser;
	t_command	*command;

	parser = NULL;
	if (app->lexer_tokens && app->lexer_tokens->token_type == PIPE)
		return (parser_double_token_error(app, app->lexer_tokens,
				app->lexer_tokens->token_type));
	count_pipes(app);
	while (app->lexer_tokens)
	{
		if (app->lexer_tokens->token_type == PIPE)
			delete_node_by_index(&app->lexer_tokens, app->lexer_tokens->index);
		if (handle_pipe_errors(app, app->lexer_tokens->token_type))
			return (EXIT_FAILURE);
		parser = init_parser(app);
		command = get_command(parser);
		if (!command)
			parser_error(0, app, parser->lexer_list);
		if (!app->commands_list)
			app->commands_list = command;
		else
			add_command_to_list(app, command);
		app->lexer_tokens = parser->lexer_list;
		free(parser);
	}
	return (EXIT_SUCCESS);
}
