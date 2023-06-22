/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:32:16 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/22 17:01:51 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

int	exec_cmd(t_command *cmd, t_app *app)
{
	if (!cmd->str[0])
		return (0);
	if (isbuiltin(cmd->path))
		return (exec_bi(cmd, app));
	else
	{
		cmd->pid = fork();
		chld_sig_config();
		if (cmd->pid == 0)
		{
			execve(cmd->path, cmd->str, app->envp);
			exit(mini_perr(PRE, cmd->str[0], 127, 0));
		}
		else if (cmd->pid < 0)
			return (mini_perr(PRE, "fork", 127, -1));
	}
	return (0);
}

int	piper(t_command *commands_list)
{
	t_command	*cmd;
	int			pp[2];

	cmd = commands_list;
	while (cmd->next)
	{
		if (pipe(pp) == -1)
			return (mini_perr(PRE, "cannot create pipe", 126, -1));
		if (cmd->fd[1] == STDOUT_FILENO)
			cmd->fd[1] = pp[1];
		else
			close(pp[1]);
		if (cmd->next->fd[0] == STDIN_FILENO)
			cmd->next->fd[0] = pp[0];
		else
			close(pp[0]);
	cmd = cmd->next;
	}
	return (0);
}

int	exec_ppx(t_app *app)
{
	int			std[2];
	t_command	*cmd;

	cmd = app->commands_list;
	std_dup(app->commands_list, &std[0], &std[1]);
	while (cmd)
	{
		dup2(cmd->fd[0], STDIN_FILENO);
		if (cmd->fd[0] != std[0])
			close(cmd->fd[0]);
		dup2(cmd->fd[1], STDOUT_FILENO);
		if (cmd->fd[1] != std[1])
			close(cmd->fd[1]);
		if (exec_cmd(cmd, app) == -1)
			break ;
		cmd = cmd->next;
	}
	if (cmd == NULL)
		g_exit_status = waiter(app->commands_list);
	else
		killer(app->commands_list);
	std_reset(std[0], std[1]);
	return (g_exit_status);
}

int	exec_simple(t_app *app)
{
	int			std[2];
	t_command	*cmd;

	cmd = app->commands_list;
	if (!cmd->str[0])
		return (g_exit_status);
	std_dup(app->commands_list, &std[0], &std[1]);
	dup2(cmd->fd[0], STDIN_FILENO);
	if (cmd->fd[0] != std[0])
		close(cmd->fd[0]);
	dup2(cmd->fd[1], STDOUT_FILENO);
	if (cmd->fd[1] != std[1])
		close(cmd->fd[1]);
	if (exec_cmd(cmd, app) > -1 && !isbuiltin(cmd->str[0]))
		g_exit_status = waiter(cmd);
	std_reset(std[0], std[1]);
	return (g_exit_status);
}

int	executor(t_app *app)
{
	t_command	*cmd;

	cmd = app->commands_list;
	while (cmd)
	{
		if (cmd->str[0])
		{
			cmd->path = cmdpath(cmd->str[0], app->env_list);
			if (!cmd->path)
				return (-1);
		}
		cmd = cmd->next;
	}
	if (redirector(app) == -1)
		return (-1);
	if (app->pipes_count > 0)
	{
		if (piper(app->commands_list) == -1)
			return (-1);
		return (exec_ppx(app));
	}
	return (exec_simple(app));
}
