/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:08:03 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/20 20:51:53 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_list	*init(char *key, char *value)
{
	t_env_list	*new;

	new = malloc(sizeof(t_env_list));
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	push_front(t_app *self, t_env_list *new)
{
	if (new == NULL)
		return ;
	if (self->env_list == NULL)
	{
		self->env_list = new;
		return ;
	}
	new->next = self->env_list;
	self->env_list = new;
}

void	fill_env_list(t_app *self, char **envp)
{
	int		i;
	int		index;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i + 1])
		i++;
	while (i >= 0)
	{
		index = 0;
		while (envp[i][index] != '=')
			index++;
		key = ft_substr(envp[i], 0, index);
		value = ft_substr(envp[i], index + 1, ft_strlen(envp[i]) - index);
		push_front(self, init(key, value));
		i--;
	}
	self->envp = ft_splitdup(envp);
}

void	remove_list_item_by_key(t_app *self, char *key)
{
	t_env_list	*tmp;
	t_env_list	*prev;

	tmp = self->env_list;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev == NULL)
				self->env_list = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	free_env_list(t_app *self)
{
	t_env_list	*tmp;
	t_env_list	*next;

	tmp = self->env_list;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next;
	}
}
