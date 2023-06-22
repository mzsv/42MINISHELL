/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:21:06 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/20 18:05:38 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>

# include "structs.h"
# include "libft.h"

typedef struct	s_parser
{
	t_lexer_token	*lexer_list;
	t_lexer_token	*redirs;
	int				redirs_count;
	struct s_app	*app;
}	t_parser;


/*
	echo $PATH hello $home hello world
	{"echo", "...", "hello", "..."}
*/

typedef struct s_command
{
	int					fd[2]; // N
	char				**str;
	char				*path; // N
	pid_t				pid; // N
	// int 				(*builtin)(t_app *, char **);
	size_t				redirs_count;
	t_lexer_token		*redirs;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

int	parser(t_app *app);

t_command *get_command(t_parser *parser);
void add_command_to_list(t_app *app, t_command *new);
char *delete_quotes(char *str, char c);
void delete_node_by_index(t_lexer_token **list, size_t index);
void collect_redirections(t_parser *parser);

#endif

/* int	piper(t_command *commands_list)
{
	t_command	*cmd;
	int			pp[2];

	cmd = commands_list;
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pp) == -1)
			{
				perror("minishell: pipe: ");
				g_exit_status = 126;
				return (-1);
			}
			if (cmd->fd[1] == STDOUT_FILENO)
				cmd->fd[1] = pp[1];
			else
				close(pp[1]);
				// close(cmd->fd[1]);
			// cmd->fd[1] = pp[1];
			if (cmd->next->fd[0] == STDIN_FILENO)
				cmd->next->fd[0] = pp[0];
			else
				close(pp[0]);
				// close(cmd->next->fd[0]);
			// cmd->next->fd[0] = pp[0];
		}
		cmd = cmd->next;
	}
	return (0);
} */