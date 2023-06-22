/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:40:50 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/15 12:11:44 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

int	isbuiltin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	bi(t_command *cmd, t_app *app)
{
	if (ft_strncmp(cmd->path, "echo", 5) == 0)
		return (ft_echo(app, cmd->str));
	else if (ft_strncmp(cmd->path, "cd", 3) == 0)
		return (ft_cd(app, cmd->str));
	else if (ft_strncmp(cmd->path, "pwd", 4) == 0)
		return (ft_pwd(app, cmd->str));
	else if (ft_strncmp(cmd->path, "export", 7) == 0)
		return (ft_export(app, cmd->str));
	else if (ft_strncmp(cmd->path, "unset", 6) == 0)
		return (ft_unset(app, cmd->str));
	else if (ft_strncmp(cmd->path, "env", 4) == 0)
		return (ft_env(app, cmd->str));
	else if (ft_strncmp(cmd->path, "exit", 5) == 0)
		return (ft_exit(app, cmd->str));
	return (0);
}

int	exec_bi(t_command *cmd, t_app *app)
{
	if (app->pipes_count > 0)
	{
		cmd->pid = fork();
		chld_sig_config();
		if (cmd->pid == 0)
		{
			exit(bi(cmd, app));
		}
		else if (cmd->pid < 0)
			return (mini_perr(PRE, "fork", 1, -1));
	}
	else
		return (bi(cmd, app));
	return (g_exit_status);
}
