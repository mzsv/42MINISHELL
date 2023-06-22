/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 22:20:09 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/20 13:59:18 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

static char	*rm_quotes(char *str)
{
	char	*del;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] != '\"' && str[i] != '\'')
			len++;
	}
	if (len == 0)
		return (ft_strdup(""));
	del = ft_calloc(len + 1, sizeof(char));
	if (!del)
		return (NULL);
	while (len > 0)
	{
		if (str[--i] != '\"' && str[i] != '\'')
			del[--len] = str[i];
	}
	return (del);
}

static void	put_expanded(char **str, char **ptr, t_env_list *envl, int fd)
{
	int		i;
	char	*key;

	i = 1;
	while (1)
	{
		if (!(*ptr)[i] || (!ft_isalnum((*ptr)[i]) && (*ptr)[i] != '_'))
		{
			key = ft_substr(*ptr, 1, i - 1);
			ft_putstr_fd(get_env_value(envl, key), fd);
			free(key);
			*str = *str + i;
			*ptr = ft_strchr(*ptr + 1, '$');
			break ;
		}
		else
			i++;
	}
}

static void	hd_expand(char *l, t_env_list *envl, int x, int fd)
{
	char	*tmp[2];

	tmp[1] = ft_strchr(l, '$');
	if (!tmp[1] || x > 0)
	{
		ft_putendl_fd(l, fd);
		return ;
	}
	tmp[0] = l;
	while (tmp[0])
	{
		if (!tmp[1])
		{
			ft_putendl_fd(tmp[0], fd);
			return ;
		}
		while (tmp[0] && tmp[0] != tmp[1])
			ft_putchar_fd(*(tmp[0]++), fd);
		if (!ft_isalpha(tmp[1][1]) && tmp[1][1] != '_')
		{
			tmp[1] = ft_strchr(tmp[1] + 1, '$');
			continue ;
		}
		put_expanded(&tmp[0], &tmp[1], envl, fd);
	}
}

static int	wr_heredoc(t_app *app, t_lexer_token *red)
{
	char	*l;
	int		fd;
	char	*del;

	fd = open("tmp_XmXiXnXiXsXhXeXlXl", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		exit(mini_perr(PRE, red->str, 1, 0));
	del = rm_quotes(red->str);
	if (!del)
		exit(mini_perr(PRE, "malloc", 1, 0));
	while (1)
	{
		l = readline("> ");
		if (!l || ft_strncmp(l, del, ft_strlen(del) + 1) == 0)
			break ;
		hd_expand(l, app->env_list, ft_strlen(red->str) - ft_strlen(del), fd);
		free(l);
	}
	if (!l)
		mini_err(PRE HDW, red->str, "\')", 0);
	free(del);
	free(l);
	close(fd);
	exit(0);
}

int	red_heredoc(t_app *app, t_lexer_token *red)
{
	pid_t	pid;
	int		fd;

	(void)app;
	pid = fork();
	if (pid == 0)
	{
		heredoc_sig_config();
		wr_heredoc(app, red);
	}
	else if (pid < 0)
		return (mini_perr(PRE, "fork", 1, -1));
	sig_ignore();
	waitpid(pid, &g_exit_status, 0);
	g_exit_status = WEXITSTATUS(g_exit_status);
	if (g_exit_status != 0)
		return (-1);
	sig_config();
	fd = open("tmp_XmXiXnXiXsXhXeXlXl", O_RDONLY);
	if (fd == -1 || unlink("tmp_XmXiXnXiXsXhXeXlXl") == -1)
		mini_perr(PRE, "here_doc", 1, 0);
	return (fd);
}
