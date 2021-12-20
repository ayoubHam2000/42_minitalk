/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:39:18 by ayoub             #+#    #+#             */
/*   Updated: 2021/12/20 13:46:21 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


void	print_bits(char c)
{
	short	i;
	char	b;

	i = 0;
	while (i < HM_OR)
	{
		b = ((c >> (HM_OR - i - 1)) & 1) + '0';
		write(1, &b, 1);
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}


int	hamming_index(int i)
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
	char	i;
	char	h;

	ft_memset(message, 0, 7);
	i = 0;
	while (i < 56)
	{
		h = hamming_index(i);
		h = ((buffer[h / 8] >> (7 - h % 8)) & 1 );
		message[i / 8] ^= (1 << (7 - (i % 8))) * h;
		i++;
	}
}

void test_add_buffer()
{
	char	bits[8];
	char	message[7];
	int		i;

	ft_memset(bits, 0, 8);
	add_to_buffer(bits, 0);
	add_to_buffer(bits, 2);
	add_to_buffer(bits, 55);
	add_parity_check(bits);
	extract_from_hamming(message, bits);
	i = 0;
	while (i < 8)
	{
		print_bits(bits[i]);
		i++;
	}
	write(1, "\n", 1);
	i = 0;
	while (i < 7)
	{
		print_bits(message[i]);
		i++;
	}
}

void test_hamming_buffer()
{
	char	bits[8];
	int		i;
	char	message[7] = {
		0b11100000,
		0b11100000,
		0b11100000,
		0b11100000,
		0b11100000,
		0b11100000,
		0b11100001
	};
	char	message_e[7];
	
	get_hamming_buffer(bits, message);
	i = 0;
	while (i < 7)
	{
		print_bits(message[i]);
		i++;
	}
	write(1, "\n", 1);
	i = 0;
	while (i < 8)
	{
		print_bits(bits[i]);
		i++;
	}

	write(1, "\n", 1);
	extract_from_hamming(message_e, bits);
	i = 0;
	while (i < 7)
	{
		print_bits(message_e[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	test_hamming_buffer();
	return (0);
}
