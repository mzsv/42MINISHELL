/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:35:23 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/19 13:21:00 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

char	*get_hostname(void)
{
	char	*tmp;
	int		fd;
	char	*host;

	fd = open("/etc/hostname", 00);
	if (fd == -1)
		return (NULL);
	tmp = get_next_line(fd);
	if (tmp == NULL)
		return (NULL);
	close(fd);
	host = ft_substr(tmp, 0, ft_strchr(tmp, '.') - tmp);
	free(tmp);
	return (host);
}

char	*prefix(char *user, char *host)
{
	char	*prefix;
	char	*tmp;

	if (user == NULL)
		user = ft_strdup("");
	if (host == NULL)
		host = ft_strdup("");
	prefix = ft_strjoin(user, "@");
	tmp = prefix;
	prefix = ft_strjoin(prefix, host);
	free(tmp);
	free(host);
	tmp = prefix;
	if (getenv("HOME"))
		prefix = ft_strjoin(prefix, ":~");
	else
		prefix = ft_strjoin(prefix, ":");
	free(tmp);
	return (prefix);
}

char	*get_rlpwd(void)
{
	char	*rlpwd;
	char	*home;
	char	*tmp;

	tmp = ft_strdup("");
	rlpwd = getcwd(NULL, 0);
	if (rlpwd == NULL)
		return (tmp);
	home = ft_strjoin(getenv("HOME"), "/");
	if (home == NULL)
		home = ft_strdup("/");
	if (ft_strncmp(rlpwd, home, ft_strlen(home)) == 0)
	{
		free(tmp);
		tmp = ft_substr(rlpwd, ft_strlen(home) - 1, ft_strlen(rlpwd));
	}
	free(rlpwd);
	free(home);
	return (tmp);
}

char	*set_prompt(void)
{
	char	*rlpwd;
	char	*ppt[2];

	ppt[0] = prefix(getenv("USER"), get_hostname());
	rlpwd = get_rlpwd();
	ppt[1] = ppt[0];
	ppt[0] = ft_strjoin(ppt[0], rlpwd);
	free(ppt[1]);
	ppt[1] = ppt[0];
	ppt[0] = ft_strjoin(ppt[0], "$ ");
	free(ppt[1]);
	ppt[1] = ppt[0];
	ppt[0] = ft_strjoin("<MINISHELL> ", ppt[0]);
	free(ppt[1]);
	free(rlpwd);
	return (ppt[0]);
}
