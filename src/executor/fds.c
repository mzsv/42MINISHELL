/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:28:52 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/15 18:23:09 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

int	set_fd(t_app *app, t_command *cmd, t_lexer_token *red, \
	int (*f)(t_app *, t_lexer_token *), int io)
{
	if (cmd->fd[io] != io)
		close(cmd->fd[io]);
	cmd->fd[io] = f(app, red);
	return (cmd->fd[io]);
}

int	std_dup(t_command *commands_list, int *stdin_dup, int *stdout_dup)
{
	t_command	*cmd;

	cmd = commands_list;
	*stdin_dup = dup(STDIN_FILENO);
	*stdout_dup = dup(STDOUT_FILENO);
	while (cmd)
	{
		if (cmd->fd[0] == STDIN_FILENO)
			cmd->fd[0] = *stdin_dup;
		if (cmd->fd[1] == STDOUT_FILENO)
			cmd->fd[1] = *stdout_dup;
		cmd = cmd->next;
	}
	return (0);
}

int	std_reset(int stdin_dup, int stdout_dup)
{
	dup2(stdin_dup, STDIN_FILENO);
	dup2(stdout_dup, STDOUT_FILENO);
	close(stdin_dup);
	close(stdout_dup);
	return (0);
}
