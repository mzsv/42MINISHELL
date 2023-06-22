/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:53:35 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/10 16:57:56 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_command	*init_command(char **str, size_t redirs_count,
		t_lexer_token *redirs)
{
	t_command	*command;

	command = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	// ft_bzero(command, sizeof(t_command));
	command->str = str;
	command->redirs_count = redirs_count;
	command->redirs = redirs;
	command->next = NULL;
	command->prev = NULL;
	return (command);
}

static size_t	count_args(t_lexer_token *list)
{
	size_t	count;

	count = 0;
	while (list && list->token_type != PIPE)
	{
		count += 1;
		list = list->next;
	}
	return (count);
}

t_command	*get_command(t_parser *parser)
{
	char			**str;
	size_t			i;
	size_t			args_count;
	t_lexer_token	*curr;

	collect_redirections(parser);
	args_count = count_args(parser->lexer_list);
	str = (char **) ft_calloc(args_count + 1, sizeof(char *));
	if (!str)
		exit(2); //! Handle
	curr = parser->lexer_list;
	i = 0;
	while (args_count > 0)
	{
		if (curr->str)
		{
			str[i] = ft_strdup(curr->str);
			delete_node_by_index(&parser->lexer_list, curr->index);
			curr = parser->lexer_list;
			i++;
		}
		args_count -= 1;
	}
	return (init_command(str, parser->redirs_count, parser->redirs));
}

void	add_command_to_list(t_app *app, t_command *new)
{
	t_command	*curr;

	if (app->commands_list == NULL)
	{
		app->commands_list = new;
		return ;
	}
	curr = app->commands_list;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	new->prev = curr;
}
