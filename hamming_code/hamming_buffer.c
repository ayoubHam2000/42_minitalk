/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hamming_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:43:01 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/20 20:29:46 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hamming_code.h"

static int	hamming_index(int i)
{
	const int	b[7] = {0, 1, 2, 4, 8, 16, 32};
	int			res;
	int			b_index;

	res = 0;
	b_index = 0;
	while (i >= 0)
	{
		if (res == b[b_index])
		{
			res++;
			b_index++;
		}
		else
		{
			i--;
			if (i >= 0)
				res++;
		}
	}
	return (res);
}

void	add_to_buffer(char *buffer, char bit)
{
	char	h;

	h = hamming_index(bit);
	buffer[h / 8] ^= (1 << (7 - h % 8));
}

void	add_parity_check(char *buffer)
{
	const int	b[] = {1, 2, 4, 8, 16, 32};
	int			i;

	i = 0;
	buffer[0] ^= (1 << 7) * parity_all(buffer);
	while (i < 6)
	{
		buffer[b[i] / 8] ^= (1 << (7 - b[i] % 8)) * parity_bc(buffer, b[i]);
		i++;
	}
}

void	get_hamming_buffer(char *buffer, char *message)
{
	char	i;
	char	h;
	char	bit;

	i = 0;
	while (i < 56)
	{
		bit = (message[i / 8] >> (7 - i % 8)) & 1;
		h = hamming_index(i);
		buffer[h / 8] ^= (1 << (7 - h % 8)) * bit;
		i++;
	}
	add_parity_check(buffer);
}

void	extract_from_hamming(char *message, char *buffer)
{
	int		i;
	char	h;

	i = 0;
	while (i < 7)
		message[i++] = 0;
	i = 0;
	while (i < 56)
	{
		h = hamming_index(i);
		h = ((buffer[h / 8] >> (7 - h % 8)) & 1);
		message[i / 8] ^= (1 << (7 - (i % 8))) * h;
		i++;
	}
}
