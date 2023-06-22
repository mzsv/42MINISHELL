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

void	delete_node_by_index(t_lexer_token **list, size_t index)
{
	t_lexer_token	*curr;

	if (*list == NULL)
		return ;
	curr = *list;
	while (curr != NULL)
	{
		if (curr->index == index)
		{
			if (curr->prev != NULL)
				curr->prev->next = curr->next;
			else
				*list = curr->next;
			if (curr->next != NULL)
				curr->next->prev = curr->prev;
		}
		curr = curr->next;
	}
}
