/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 01:46:06 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/19 12:53:52 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static int	set_pwd(t_app *self, char *oldpwd)
{
	char		*pwd[2];
	char		*old1;

	pwd[0] = getcwd(NULL, 0);
	if (pwd[0] == NULL)
		return (mini_perr(PRE, "cd", 1, 0));
	pwd[1] = ft_strjoin("PWD=", pwd[0]);
	old1 = ft_strjoin("OLDPWD=", oldpwd);
	if (find_env_key(self->env_list, "OLDPWD") == 0)
	{
		add_envlist_item(&self, old1);
		free(oldpwd);
	}
	else
		set_env_value(self->env_list, "OLDPWD", oldpwd);
	free(old1);
	if (find_env_key(self->env_list, "PWD") == 0)
	{
		add_envlist_item(&self, pwd[1]);
		free(pwd[0]);
	}
	else
		set_env_value(self->env_list, "PWD", pwd[0]);
	free(pwd[1]);
	return (EXIT_SUCCESS);
}

static int	chto_home(t_env_list *env_list)
{
	char	*home;

	home = get_env_value(env_list, "HOME");
	if (home == NULL)
		return (mini_err(PRE, "cd: ", "HOME not set", 1));
	if (chdir(home) != EXIT_SUCCESS)
		return (mini_perr(PRE "cd: ", home, 1, 0));
	g_exit_status = 0;
	return (g_exit_status);
}

int	ft_cd(t_app *self, char **args)
{
	char	*oldpwd;

	if (count_args(args) > 2)
		return (mini_err(PRE, "cd: ", "too many arguments", 1));
	oldpwd = getcwd(NULL, 0);
	if (args[1] == NULL)
	{
		if (chto_home(self->env_list) != EXIT_SUCCESS)
			return (g_exit_status);
	}
	else
	{
		if (chdir(args[1]) != EXIT_SUCCESS)
			return (mini_perr(PRE "cd: ", args[1], 1, 0));
		g_exit_status = 0;
	}
	set_pwd(self, oldpwd);
	return (g_exit_status);
}
