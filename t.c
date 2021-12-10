/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:39:18 by ayoub             #+#    #+#             */
/*   Updated: 2021/12/10 23:25:57 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void extractfromsize_t()
{
	size_t a;
	char c;
	int i;
	
	a = 300; //0000 0001 0010 1100
	i = 0;
	while (i < 8)
	{
		c = *((char *)(&a));
		printf("%d\n", c);
		a = a >> 8;
		i++;
	}
}

int main(int ac, char **av)
{
	size_t a;
	int i;

	char b[] = {44, 1, 0, 0, 0, 0, 0, 0};
	
	a = 0;
	char *c = (char *)(&a);
	i = 0;
	while (i < 8)
	{
		*(c + i) = b[i];
		i++;
	}
	printf("%lu\n", a);
	return (0);	
}