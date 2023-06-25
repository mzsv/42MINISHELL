/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:37:55 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/25 12:50:57 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include "minishell.h"

typedef struct s_dll_item
{
	void				*data;
	struct s_dll_item	*next;
	struct s_dll_item	*prev;
}	t_dll_item;

void		print_dll_list(t_dll_item *head_ref, void (*f)(void *));
void		dll_append(t_dll_item **head_ref, void *new_data);
void		dll_push(t_dll_item **head_ref, void *new_data);
void		free_dll_list(t_dll_item *head_ref, void (*f)(void *));
int			count_symbol_in_string(char *str, int ch);
t_env_list	*init(char *key, char *value);
void		push_front(t_app *self, t_env_list *new);
void		free_command_list(t_command **list);
void		reset(t_app *app);
void		terminate(t_app **app);

#endif
