/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:06:02 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/15 18:08:30 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

static void	heredoc_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_exit_status = 128 + SIGINT;
		unlink("tmp_XmXiXnXiXsXhXeXlXl");
		exit(g_exit_status);
	}
}

int	heredoc_sig_config(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = &heredoc_ctrl_c;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (mini_perr(PRE, "sigaction", 1, 0));
	return (0);
}

int	sig_ignore(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (mini_perr(PRE, "sigaction", 1, 0));
	return (0);
}
