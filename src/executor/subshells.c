/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:44:11 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/26 19:29:47 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

int	waiter(t_command *commands_list)
{
	t_command	*cmd;
	int			wstatus;

	cmd = commands_list;
	wstatus = 0;
	while (waitpid(0, &wstatus, 0) > 0)
		;
	g_exit_status = WEXITSTATUS(wstatus);
	return (g_exit_status);
}

int	killer(t_command *commands_list)
{
	t_command	*cmd;

	cmd = commands_list;
	while (cmd)
	{
		if (cmd->pid != 0)
			kill(cmd->pid, SIGKILL);
		cmd = cmd->next;
	}
	return (0);
}
