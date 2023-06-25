/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:43:48 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/25 12:44:15 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error.h"
#include <stdio.h>

void	parser_error(int error, t_app *app, t_lexer_token *lexer_list)
{
	ft_lexerclear(&lexer_list);
	ft_error(error, app);
}

int	pdte(t_app *app, t_lexer_token *lexer_list,
								t_token_type token)
{
	(void)app;
	(void)lexer_list;
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (token == GREAT)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token == G_GREAT)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (token == LESS)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token == L_LESS)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (token == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
