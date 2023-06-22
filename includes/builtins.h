/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:46:32 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/20 20:43:16 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <signal.h>
# include "minishell.h"

int		ft_cd(t_app *self, char **args);

int		ft_echo(t_app *self, char **args);

int		ft_env(t_app *self, char **args);

int		ft_exit(t_app *self, char **args);

int		ft_export(t_app *self, char **args);

int		ft_pwd(t_app *self, char **args);

int		ft_unset(t_app *self, char **args);

int		sig_config(void);

int		find_env_key(t_env_list *env_list, char *key);

char	*get_env_value(t_env_list *env_list, char *key);

int		set_env_value(t_env_list *env_list, char *key, char *value);

int		env_list_size(t_env_list *env_list);

void	add_envlist_item(t_app **self, char *arg);

t_app	*env_list_dup(t_env_list *env_list);

int		find_env_key(t_env_list *env_list, char *key);

void	envl_dup_clear(t_app **self);

char	**getenvp(t_env_list *env_list);

#endif
