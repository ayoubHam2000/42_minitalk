/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:38:44 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/04 16:00:11 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
#define MAX 2147483648

int	g_action = - 1;

void handler_zero(int a)
{
	//write(1, "-", 1);
	g_action = 0;
}

void handler_one(int a)
{
	//write(1, "*", 1);
	g_action = 1;
}

int	collect(unsigned int *num, unsigned int	*mul)
{
	static	int how = 0;

	if (g_action == 1)
	{
		*num += *mul;
	}
	if (*mul < 2147483648)
		*mul *= 2;
	else
		*mul = 1;
	how++;
	if (how == 32)
	{
		how = 0;
		return (1);
	}
	return (0);
}

int main()
{
	unsigned int mul;
	unsigned int res;

	printf("%d\n", getpid());	
	signal(SIGUSR1, handler_zero);
	signal(SIGUSR2, handler_one);
	mul = 1;
	res = 0;
	while (1)
	{
		pause();
		if ((g_action == 1 || g_action == 0))
		{
			if (collect(&res, &mul))
			{
				write(1, &res, 1);
				res = 0;
			}
			g_action = -1;
		}
	}
	return (0);
}
