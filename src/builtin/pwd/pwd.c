/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:31:20 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/17 16:30:16 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

int	ft_pwd(t_app *self, char **args)
{
	char	*pwd;

	(void)self;
	(void)args;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (mini_perr(PRE, "pwd", 1, 0));
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	g_exit_status = 0;
	return (g_exit_status);
}
