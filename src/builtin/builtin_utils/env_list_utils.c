/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:53:23 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/18 18:56:25 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_env_key(t_env_list *env_list, char *key)
{
	t_env_list	*envl;

	if (!env_list)
		return (0);
	envl = env_list;
	while (envl)
	{
		if (ft_strncmp(envl->key, key, ft_strlen(key) + 1) == 0)
			return (1);
		envl = envl->next;
	}
	return (0);
}

char	*get_env_value(t_env_list *env_list, char *key)
{
	t_env_list	*tmp;

	if (!env_list)
		return (NULL);
	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	set_env_value(t_env_list *env_list, char *key, char *value)
{
	t_env_list	*tmp;

	if (!env_list || !value || value[0] == '\0')
		return (0);
	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	env_list_size(t_env_list *env_list)
{
	int			size;
	t_env_list	*tmp;

	size = 0;
	tmp = env_list;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}
