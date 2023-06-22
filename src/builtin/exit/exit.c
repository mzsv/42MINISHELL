/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 22:41:34 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/20 19:30:57 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

static int	verify_num_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

long long	atoll_check(const char *nptr)
{
	unsigned long long	res;
	int					sign;

	sign = 1;
	res = 0;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	if (ft_strlen(nptr) > 19)
		return (-1);
	while ((*nptr >= 48 && *nptr <= 57) && *nptr)
	{
		res = res * 10 + *nptr - '0';
		nptr++;
	}
	if (res == 0)
		return (res);
	if ((sign > 0 && res > LLONG_MAX) || (sign < 0 && res - 1 >= LLONG_MAX))
		return (-1);
	if (res == 1 && sign < 0)
		return (255);
	return (res * sign);
}

int	get_exit_status(char *arg)
{
	long long	status;

	status = atoll_check(arg);
	if (status == -1)
		return (mini_err(PRE "exit: ", arg, ": numeric argument required", 2));
	if (status > 255)
		return (status % 256);
	if (status < 0)
		return (256 - ((-status) % 256));
	return (status);
}

int	ft_exit(t_app *self, char **args)
{
	(void)self;
	if (self->pipes_count == 0)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (args[1] && verify_num_arg(args[1]) == 0)
		g_exit_status = 2;
	else if (args[1] && verify_num_arg(args[1]) == 1)
	{
		if (args[2])
			return (mini_err(PRE "exit: ", NULL, "too many arguments", 127));
		else
			g_exit_status = get_exit_status(args[1]);
	}
	terminate(&self);
	return (g_exit_status);
}
