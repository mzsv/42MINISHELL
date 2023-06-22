/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:54:21 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/03 21:47:09 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	find_next_quote(char *line, int start, int *count, char quote)
{
	int	i;

	i = start + 1;
	*count += 1;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
		*count += 1;
	return (i - start);
}

int	check_quotes(char *line)
{
	int	i;
	int	doubl;
	int	single;

	doubl = 0;
	single = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			i += find_next_quote(line, i, &single, '\'');
		if (line[i] == '"')
			i += find_next_quote(line, i, &doubl, '"');
		i++;
	}
	if ((doubl > 0 && doubl % 2 != 0) || (single > 0 && single % 2 != 0))
		return (0);
	return (1);
}

int	handle_quotes(int start, char *str, char quote)
{
	int	i;

	i = start;
	if (str[i] == quote)
	{
		i++;
		while (str[i] && str[i] != quote)
			i++;
		i++;
	}
	return (i);
}
