/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:25:45 by ayoub             #+#    #+#             */
/*   Updated: 2021/12/22 18:30:51 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#define POLYNOMIAL 0b10011011

unsigned char	crc(unsigned char message)
{
	unsigned char	remainder;
	int				bit;

	remainder = message;
	bit = 7;
	while (bit >= 0)
	{
		if (remainder & 0b10000000)
			remainder ^= POLYNOMIAL;
		remainder = (remainder << 1);
		bit--;
	}
	return (remainder >> 1);
}

void	print_bits(char c)
{
	short	i;
	char	b;

	i = 0;
	while (i < 8)
	{
		b = ((c >> (8 - i - 1)) & 1) + '0';
		write(1, &b, 1);
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

int	main(void)
{
	char	c;

	c = crc(156);
	print_bits(c);
}
