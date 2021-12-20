/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hamming_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:06:57 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/20 20:50:39 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hamming_code.h"

static char	hamming_gete(char *bits)
{
	int		i;
	char	p;
	char	c;
	int		counter;

	i = HM_OR * HM_OR / 2;
	counter = HM_OR - 3;
	c = 0;
	while (i > 0)
	{
		p = bits[i / HM_OR];
		p = (p >> (HM_OR - 1 - i % HM_OR)) & 1;
		c = c + (1 << counter) * (p ^ parity_bc(bits, i));
		counter--;
		i = i / 2;
	}
	return (c);
}

/*
res <=> c
b <=> p
c = 0 and p = 0 No error
c = 0 and p = 1 Error has occurred in the P bit.
c != 0 and p = 0 Single bit error occurred in position c that can be
corrected
c != 0 and p = 1 Double error detected that cannot be corrected
*/

char	hammingc(char *bits)
{
	char	p;
	char	c;

	c = hamming_gete(bits);
	p = (bits[0] >> (HM_OR - 1)) & 1;
	p = (p ^ parity_all(bits));
	if (c == 0)
		return (0);
	if (c != 0 && p == 0)
		return (1);
	bits[c / HM_OR] ^= (1 << (HM_OR - 1 - (c % HM_OR)));
	return (0);
}

/*
int main(int ac, char **av)
{
	char bits[HM_OR] = {
		0b00001101, //byte1
		0b10000000, //byte2
		0b10000000, //byte3
		0b10010100, //byte4
		
		0b10001000, //byte5
		0b11000111, //byte6
		0b10110011, //byte7
		0b10000011, //byte8
	};

	print_bits(parity_v(bits));
	print_bits(parity_h(bits));
	//printf("%d\n", parity_l(bits[1]));
	// printf("%d\n", parity_bc(bits, 1));
	//printf("%d\n", parity_all(bits));
	//printf("%d\n", parity_bc(bits, 16));
	char c = hamming_gete(bits);
	print_bits(c);
	printf("%d\n", c);
	printf("error => %d\n--------------------\n", hammingc(bits));
	int i = 0;
	while (i < 8)
		print_bits(bits[i++]);
	
	//char tt = 0b11010100;
	//print_bits(tt - (1 << 6));

	return (0);
}
*/
