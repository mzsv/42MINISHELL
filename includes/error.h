/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 20:59:12 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/25 12:41:33 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
#define ERROR_H

# include "minishell.h"

void	parser_error(int error, t_app *app, t_lexer_token *lexer_list);
int	handle_pipe_errors(t_app *app, t_token_type token_type);
void	lexer_error(int error, t_app *app);
int		ft_error(int error, t_app *app);
int		pdte(t_app *app, t_lexer_token *lexer_list,
	t_token_type token);

#endif
