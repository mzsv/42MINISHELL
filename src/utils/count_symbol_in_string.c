/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_symbol_in_string.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:58:54 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/25 20:31:44 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	count_symbol_in_string(char *str, int ch)
{
	int	count;

	count = 0;
	if (!str)
		return (count);
	while (*str)
	{
		if (*str == ch)
			count++;
		str++;
	}
	return (count);
}
