/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:07:47 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/22 22:13:04 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

static void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 128 + SIGINT;
	}
}

static void	chld_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_exit_status = 128 + SIGINT;
	}
}

int	chld_sig_config(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = &chld_ctrl_c;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (mini_perr(PRE, "sigaction", 1, 0));
	return (0);
}

int	sig_config(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_int.sa_handler = &ctrl_c;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (mini_perr(PRE, "sigaction", 1, 0));
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		return (mini_perr(PRE, "sigaction", 1, 0));
	return (EXIT_SUCCESS);
}
