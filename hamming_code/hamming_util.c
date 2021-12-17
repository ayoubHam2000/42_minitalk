/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hamming_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 19:56:34 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/17 19:59:31 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hamming_code.h"

char	parity_l(char c)
{
	int		i;
	char	res;

	res = 0;
	i = 0;
	while (i++ < HM_OR)
	{
		res = res ^ (c & 1);
		c = c >> 1;
	}
	return (res);
}

char	parity_v(char *bits)
{
	short	i;
	char	res;

	i = 0;
	res = 0;
	while (i < HM_OR)
	{
		res = res ^ bits[i];
		i++;
	}
	return (res);
}

char	parity_h(char *bits)
{
	short	i;
	char	res;

	i = HM_OR - 1;
	res = 0;
	while (i >= 0)
	{
		res = res + (parity_l(bits[HM_OR - i - 1]) << i);
		i--;
	}
	return (res);
}

char	parity_bc(char *bits, int nb)
{
	int		i;
	int		res;
	char	c;
	char	b;

	b = bits[nb / HM_OR];
	b = (b >> (HM_OR - 1 - nb % HM_OR)) & 1;
	if (nb >= HM_OR)
	{
		c = parity_h(bits);
		nb = nb / HM_OR;
	}
	else
		c = parity_v(bits);
	i = nb;
	res = 0;
	while (i < HM_OR)
	{
		res = res ^ ((c >> (HM_OR - 1 - i)) & 1);
		i++;
		if ((i / nb) % 2 == 0)
			i = i + nb;
	}
	return (res ^ b);
}

char	parity_all(char *bits)
{
	char	first_bit;

	first_bit = (bits[0] >> (HM_OR - 1)) & 1;
	return (parity_l(parity_v(bits)) ^ first_bit);
}
