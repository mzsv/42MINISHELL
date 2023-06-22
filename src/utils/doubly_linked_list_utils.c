/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:24:35 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/20 14:22:29 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	free_dll_list(t_dll_item *head_ref, void (*f)(void *))
{
	t_dll_item	*curr;
	t_dll_item	*tmp;

	curr = head_ref;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		f(tmp->data);
		free(tmp);
	}
}

void	print_dll_list(t_dll_item *head_ref, void (*f)(void *))
{
	if (head_ref == NULL)
		printf("List is empty!\n");
	while (head_ref)
	{
		f(head_ref->data);
		head_ref = head_ref->next;
	}
}

void	dll_push(t_dll_item **head_ref, void *new_data)
{
	t_dll_item	*new_node;

	new_node = (t_dll_item *) malloc(sizeof(t_dll_item));
	new_node->data = new_data;
	new_node->next = (*head_ref);
	new_node->prev = NULL;
	if ((*head_ref) != NULL)
		(*head_ref)->prev = new_node;
	(*head_ref) = new_node;
}

void	dll_append(t_dll_item **head_ref, void *new_data)
{
	t_dll_item	*new_node;
	t_dll_item	*last;

	new_node = (t_dll_item *) malloc(sizeof(t_dll_item));
	last = *head_ref;
	new_node->data = new_data;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		new_node->prev = NULL;
		*head_ref = new_node;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	return ;
}
