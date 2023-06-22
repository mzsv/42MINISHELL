/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 20:02:37 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/19 18:10:13 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_exit_status;

static int	isalphanum_(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
	}
	return (1);
}

static int	check_args(char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		if (!isalphanum_(args[i]))
			return (mini_err(PRE "unset: `", args[i], \
				"': not a valid identifier", 1));
	}
	return (0);
}

int	ft_unset(t_app *self, char **args)
{
	int	i;

	if (check_args(args) != 0)
		return (g_exit_status);
	i = 0;
	while (args[++i])
		remove_list_item_by_key(self, args[i]);
	g_exit_status = 0;
	return (g_exit_status);
}
