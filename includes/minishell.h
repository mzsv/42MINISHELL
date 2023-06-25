/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:47:01 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/25 12:49:10 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
# include <stddef.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "utils.h"
# include "builtins.h"
# include "structs.h"
# include "error.h"
# include "executor.h"

# define BLUEB	"\033[0;34m\033[1m"
# define GRNB	"\033[0;32m\033[1m"
# define YELB	"\033[0;33m\033[1m"
# define DFT	"\033[0m"

void	fill_env_list(t_app *self, char **envp);
void	free_env_list(t_app *self);
void	remove_list_item_by_key(t_app *self, char *key);
int		env(t_app **self, char **args);

char	*ft_readline(char *prompt);

#endif
