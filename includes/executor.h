/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:59:30 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/20 20:42:20 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>
# include <sys/wait.h>
# include "minishell.h"

# define PRE "minishell: "
# define HDW "warning: here-document delimited by end-of-file (wanted `"

char	**ft_splitdup(char **str);

int		sig_ignore(void);

int		heredoc_sig_config(void);

int		chld_sig_config(void);

int		mini_err(char *pre, char *name, char *msg, int exit_status);

int		mini_perr(char *pre, char *name, int exit_status, int fail);

void	ft_splitfree(char **str);

int		red_out(t_app *app, t_lexer_token *red);

int		red_append(t_app *app, t_lexer_token *red);

int		red_in(t_app *app, t_lexer_token *red);

int		red_heredoc(t_app *app, t_lexer_token *red);

int		set_fd(t_app *app, t_command *cmd, t_lexer_token *red, \
	int (*f)(t_app *, t_lexer_token *), int io);

int		redirector(t_app *app);

int		isbuiltin(char *cmd);

int		bi(t_command *cmd, t_app *app);

int		exec_bi(t_command *cmd, t_app *app);

int		exec_cmd(t_command *cmd, t_app *app);

int		piper(t_command *commands_list);

int		waiter(t_command *commands_list);

int		killer(t_command *commands_list);

int		std_dup(t_command *commands_list, int *stdin_dup, int *stdout_dup);

int		std_reset(int stdin_dup, int stdout_dup);

int		exec_ppx(t_app *app);

char	*pathsearch(char *cmd, char **paths);

char	*cmdpath(char *cmd, t_env_list *envl);

int		exec_simple(t_app *app);

int		executor(t_app *app);

char	*get_hostname(void);

char	*get_rlpwd(void);

char	*set_prompt(void);

#endif