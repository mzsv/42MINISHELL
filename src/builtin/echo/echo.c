/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:39:39 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/15 18:17:30 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

static int	set_option(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		if (ft_strncmp(args[i], "-n", 2) == 0)
		{
			j = 1;
			while (args[i][j])
			{
				if (args[i][j] != 'n')
					return (i);
				j++;
			}
		}
		else
			return (i);
	}
	return (i);
}

int	ft_echo(t_app *self, char **args)
{
	int	i;
	int	n;

	(void)self;
	n = set_option(args);
	i = n;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (n == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_exit_status = 0;
	return (g_exit_status);
}
