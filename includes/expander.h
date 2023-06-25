/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:47:58 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/25 12:48:18 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

int		expander(t_app *app);

void	free_strs(char **strs);
bool	is_var_name(char c);
char	*strings_join(char **strs);

size_t	expand_dollar_sign(char *str, size_t start, char **line,
			t_env_list *list);
size_t	expand_single_quotes(char *str, size_t start, char **line);
size_t	expand_double_quotes(char *str, size_t start, char **line,
			t_env_list *list);
size_t	expand_plain_text(const char *str, size_t start, char **line);
size_t	expand_backslash(const char *str, size_t start, char **line);

#endif
