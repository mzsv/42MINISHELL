/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:39:34 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/20 14:00:45 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
} t_env_list;

typedef enum s_token_type
{
    WORD = 0,
	PIPE,
	GREAT,
	G_GREAT,
	LESS,
	L_LESS
}	t_token_type;

typedef struct s_lexer_token
{




	size_t 					index;
	char					*str;
	t_token_type			token_type;
	struct s_lexer_token	*next;
	struct s_lexer_token	*prev;

}	t_lexer_token;

typedef struct s_app
{
	t_env_list			*env_list;
	char				**envp;
	char				*input;
	t_lexer_token		*lexer_tokens;
	struct s_command	*commands_list;
	int					pipes_count;

	// int *pid;
	// bool heredoc;
	// bool reset;
} t_app;

#endif
