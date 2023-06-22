/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:44:11 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/22 22:12:41 by amenses-         ###   ########.fr       */
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
	sig_ignore();
	while (cmd)
	{
		if (cmd->str[0])
			waitpid(0, &wstatus, 0);
		cmd = cmd->next;
	}
	sig_config();
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
