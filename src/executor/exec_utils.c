/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:51:21 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/20 20:41:37 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

extern int	g_exit_status;

int	mini_err(char *pre, char *name, char *msg, int exit_status)
{
	ft_putstr_fd(pre, STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	g_exit_status = exit_status;
	return (g_exit_status);
}

int	mini_perr(char *pre, char *name, int exit_status, int fail)
{
	ft_putstr_fd(pre, STDERR_FILENO);
	perror(name);
	g_exit_status = exit_status;
	if (fail == -1)
		return (-1);
	return (g_exit_status);
}

char	**ft_splitdup(char **str)
{
	int		i;
	char	**dup;

	i = 0;
	while (str[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	while (--i >= 0)
		dup[i] = ft_strdup(str[i]);
	return (dup);
}

void	ft_splitfree(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
