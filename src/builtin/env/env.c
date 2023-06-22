/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:09:01 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/20 20:50:28 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_exit_status;

int	ft_env(t_app *self, char **args)
{
	int	i;

	if (args[1])
		return (mini_err("env: `", args[1], \
			"`: No such file or directory", 127));
	i = -1;
	while (self->envp[++i])
		printf("%s\n", self->envp[i]);
	g_exit_status = 0;
	return (g_exit_status);
}
