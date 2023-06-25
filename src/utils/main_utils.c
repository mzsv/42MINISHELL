/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:30:14 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/25 12:05:33 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

void	free_command_list(t_command **list)
{
	t_command	*cmd;
	t_command	*prev;

	cmd = *list;
	while (cmd)
	{
		if (cmd->str)
			ft_splitfree(cmd->str);
		if (cmd->path)
			free(cmd->path);
		ft_lexerclear(&(cmd->redirs));
		prev = cmd;
		cmd = cmd->next;
		free(prev);
	}
	*list = NULL;
}

void	reset(t_app *app)
{
	if (app->lexer_tokens)
		ft_lexerclear(&(app->lexer_tokens));
	app->lexer_tokens = NULL;
	if (app->input)
		free(app->input);
	app->input = NULL;
	if (app->commands_list)
		free_command_list(&(app->commands_list));
	app->commands_list = NULL;
}

void	terminate(t_app **app)
{
	reset(*app);
	free_env_list(*app);
	ft_splitfree((*app)->envp);
	free(*app);
	*app = NULL;
	exit(g_exit_status);
}
