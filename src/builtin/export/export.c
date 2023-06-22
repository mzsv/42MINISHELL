/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:22:40 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/20 20:51:23 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

static int	validate_key(char *arg)
{
	int		i;
	char	*del;
	int		index;

	del = ft_strchr(arg, '=');
	if (del == NULL)
		index = ft_strlen(arg);
	else
		index = (int)(del - arg);
	if (index == 0)
		return (0);
	if (arg[0] == '*' && (arg[1] != '\0' || arg[1] != ';'))
		return (0);
	else if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 0;
	while (i < index)
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	export_display(t_env_list *env_list)
{
	t_env_list	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (tmp->value == NULL)
			printf("declare -x %s\n", tmp->key);
		else
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

static void	sorted_display(t_app *self_dup)
{
	t_env_list	*tmp[2];
	char		*tmp_key_val[2];

	tmp[0] = self_dup->env_list;
	while (tmp[0])
	{
		tmp[1] = tmp[0]->next;
		while (tmp[1])
		{
			if (ft_strncmp(tmp[0]->key, tmp[1]->key, \
				ft_strlen(tmp[0]->key) + ft_strlen(tmp[1]->key)) > 0)
			{
				tmp_key_val[0] = tmp[0]->key;
				tmp_key_val[1] = tmp[0]->value;
				tmp[0]->key = tmp[1]->key;
				tmp[0]->value = tmp[1]->value;
				tmp[1]->key = tmp_key_val[0];
				tmp[1]->value = tmp_key_val[1];
			}
			tmp[1] = tmp[1]->next;
		}
		tmp[0] = tmp[0]->next;
	}
	export_display(self_dup->env_list);
}

int	ft_export(t_app *self, char **args)
{
	int		i;
	t_app	*self_dup;

	i = 1;
	if (args[1] == NULL)
	{
		self_dup = env_list_dup(self->env_list);
		if (self_dup == NULL && args[1] == NULL)
			return (mini_perr(PRE, "export", 1, 0));
		sorted_display(self_dup);
		envl_dup_clear(&self_dup);
		g_exit_status = 0;
	}
	while (args[i])
	{
		if (validate_key(args[i]))
			add_envlist_item(&self, args[i]);
		else
			mini_err(PRE "export: `", args[i], "': not a valid identifier", 1);
		i++;
	}
	ft_splitfree(self->envp);
	self->envp = getenvp(self->env_list);
	return (g_exit_status);
}
