/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:56:58 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/25 12:37:09 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parser.h"
#include "../../includes/error.h"

static void	push_back(t_lexer_token **list, t_lexer_token *new)
{
	t_lexer_token	*curr;

	if (*list == NULL)
	{
		new->prev = NULL;
		*list = new;
		return ;
	}
	curr = *list;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	new->prev = curr;
}

void	add_new_redirect(t_parser *parser, t_lexer_token *token)
{
	t_lexer_token	*new;
	size_t			first;
	size_t			second;

	new = get_lexer_new_node(ft_strdup(token->next->str), token->token_type);
	if (!new)
		parser_error(1, parser->app, parser->lexer_list);
	push_back(&parser->redirs, new);
	first = token->index;
	second = token->next->index;
	delete_node_by_index(&parser->lexer_list, first);
	delete_node_by_index(&parser->lexer_list, second);
	parser->redirs_count += 1;
}

void	collect_redirections(t_parser *parser)
{
	t_lexer_token	*curr;

	curr = parser->lexer_list;
	while (curr && curr->token_type == WORD)
		curr = curr->next;
	if (curr == NULL || curr->token_type == PIPE)
		return ;
	if (curr->next == NULL)
		parser_error(0, parser->app, parser->lexer_list);
	if (curr->next->token_type > WORD)
		parser_double_token_error(parser->app,
			parser->lexer_list, curr->next->token_type);
	if (curr->token_type >= GREAT && curr->token_type <= L_LESS)
		add_new_redirect(parser, curr);
	collect_redirections(parser);
}
