/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:20:06 by amenses-          #+#    #+#             */
/*   Updated: 2022/11/24 07:02:49 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_emptypocket(char **pocket)
{
	if (*pocket != NULL && !ft_findchr(*pocket, '\0'))
	{
		free(*pocket);
		*pocket = NULL;
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*pocket;
	char		*l;
	ssize_t		n;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	n = 1;
	while (n > 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n >= 0)
			buffer[n] = '\0';
		else
			buffer[0] = '\0';
		pocket = ft_strjoinfree(pocket, buffer);
		l = ft_getl(pocket, &n);
		pocket = ft_fillpocket(pocket, &n);
	}
	ft_emptypocket(&pocket);
	free(buffer);
	return (l);
}
/* int main(int argc, char **argv)
{
	int fd;
	char *line;
	size_t i;

	(void)argc;
	(void)argv;
	if (argc > 1)
	{
		fd = open(argv[1], 00);
		i = 0;
		while (i < 4)
		{
			line = get_next_line(fd);
			printf("result(%ld)=.%s.\n", i, line);
			free(line);
			i++;
		}
		close(fd);
	}
	else
	{
		fd = 0;
		i = 0;
		line = get_next_line(fd);
		printf("result(%ld)=.%s.", i, line);
		free(line);
	}
	return (0);
} */