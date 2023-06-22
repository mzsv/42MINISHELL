/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:11:46 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/20 20:46:47 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_envlist_item(t_app **self, char *arg)
{
	t_env_list	*new;
	char		*del;
	int			index;
	char		*item[2];

	del = ft_strchr(arg, '=');
	ft_bzero(item, sizeof(char *) * 2);
	if (del == NULL)
		index = ft_strlen(arg);
	else
		index = (int)(del - arg);
	item[0] = ft_substr(arg, 0, index);
	if (del != NULL)
		item[1] = ft_substr(arg, index + 1, ft_strlen(arg));
	if (find_env_key((*self)->env_list, item[0]))
	{
		set_env_value((*self)->env_list, item[0], item[1]);
		free(item[0]);
	}
	else
	{
		new = init(item[0], item[1]);
		push_front(*self, new);
	}
}

t_app	*env_list_dup(t_env_list *env_list)
{
	t_app		*new;
	t_env_list	*tmp;

	tmp = env_list;
	new = ft_calloc(1, sizeof(t_app));
	if (new == NULL)
		return (NULL);
	while (tmp)
	{
		if (tmp->value == NULL)
			push_front(new, init(ft_strdup(tmp->key), NULL));
		else
			push_front(new, init(ft_strdup(tmp->key), ft_strdup(tmp->value)));
		tmp = tmp->next;
	}
	return (new);
}

void	envl_dup_clear(t_app **self)
{
	t_env_list	*tmp;
	t_env_list	*next;

	tmp = (*self)->env_list;
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
	free(*self);
}

static char	**init_envp(t_env_list *env_list)
{
	char		**envp;
	t_env_list	*tmp_lst;
	int			i;

	tmp_lst = env_list;
	i = 0;
	while (tmp_lst)
	{
		if (tmp_lst->value)
			i++;
		tmp_lst = tmp_lst->next;
	}
	envp = ft_calloc(i + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	return (envp);
}

char	**getenvp(t_env_list *env_list)
{
	char		**envp;
	char		*tmp;
	int			i;
	t_env_list	*tmp_lst;

	envp = init_envp(env_list);
	tmp = NULL;
	tmp_lst = env_list;
	i = 0;
	while (tmp_lst)
	{
		if (tmp_lst->value)
		{
			tmp = ft_strjoin(tmp_lst->key, "=");
			envp[i++] = ft_strjoin(tmp, tmp_lst->value);
			free(tmp);
		}
		tmp_lst = tmp_lst->next;
	}
	return (envp);
}
