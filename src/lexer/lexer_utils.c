/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:50:52 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/05 21:01:31 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_lexer_token	*get_lexer_new_node(char *str, int token_type)
{
	t_lexer_token	*new;
	static int		i = 0;

	new = (t_lexer_token *)malloc(sizeof(t_lexer_token));
	if (!new)
		return (NULL);
	new->index = i++;
	new->str = str;
	new->token_type = token_type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static void	push_back(t_lexer_token **list, t_lexer_token *node)
{
	t_lexer_token	*curr;

	curr = *list;
	if (curr == NULL)
	{
		*list = node;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = node;
	node->prev = curr;
}

int	add_node(char *str, t_token_type token_type, t_lexer_token **list)
{
	t_lexer_token	*node;

	node = get_lexer_new_node(str, token_type);
	if (!node)
		return (0);
	push_back(list, node);
	return (1);
}

void	ft_lexerclear(t_lexer_token **lst)
{
	t_lexer_token	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->str)
			free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
