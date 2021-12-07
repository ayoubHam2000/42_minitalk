/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:39:18 by ayoub             #+#    #+#             */
/*   Updated: 2021/12/07 19:07:33 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	tobinary(unsigned int a)
{
	unsigned int	i;
	unsigned int	op;
	unsigned int	bit;

	i = 0;
	op = 1;
	while (++i < UNIT_SIZE)
		op = op * 2;
	i = 0;
	while (i < UNIT_SIZE)
	{
		bit = (a & op) / op;
		if (bit)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		a = (a << 1);
		i++;
	}
}

int main()
{
	unsigned int a = 1;
	
	a = (unsigned int)1 << 6;
	tobinary(a);
	printf("\n%u", a);
	return (0);	
}