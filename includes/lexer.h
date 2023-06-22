/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:48:16 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/05 21:01:28 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "structs.h"

int				lexer(t_app *app);
int				check_quotes(char *line);
int				handle_quotes(int start, char *str, char quote);
int				add_node(char *str, t_token_type token_type, t_lexer_token **list);
t_lexer_token	*get_lexer_new_node(char *str, int token_type);
int				get_tokens(t_app *app);
void			ft_lexerclear(t_lexer_token **lst);

#endif
