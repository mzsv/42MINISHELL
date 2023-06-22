/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:57:03 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/03 21:57:06 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
void	free_lexer_node(t_lexer_token *token)
{
	if (!token)
		return ;
	if (token->str)
		free(token->str);
	free(token);
}

void	delete_node_by_index(t_lexer_token **list, size_t index)
{
	t_lexer_token	*curr;
	t_lexer_token	*to_delete;

	if (*list == NULL)
		return ;
	curr = *list;
	to_delete = NULL;
	while (curr != NULL)
	{
		if (curr->index == index)
		{
			to_delete = curr;
			if (curr->prev != NULL)
				curr->prev->next = curr->next;
			else
				*list = curr->next;
			if (curr->next != NULL)
				curr->next->prev = curr->prev;
			break ;
		}
		curr = curr->next;
	}
	free_lexer_node(to_delete);
}
