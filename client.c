/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:50:51 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/04 16:01:21 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#define PART_SIZE 32

void send_int(int receiver, int a)
{
	int	i;

	i = 0;
	while (i < PART_SIZE)
	{
		if (a % 2)
			kill(receiver, SIGUSR2);
		else
			kill(receiver, SIGUSR1);
		i++;
		printf("Send To %d c = %d n = %d\n", receiver, a % 2, i);
		a = a / 2;
		usleep(50);
	}
}

int main(int ac, char **av)
{
	int		server_pid;
	char	*data;

	if (ac < 3)
		return (1);
	server_pid = atoi(av[1]);
	data = av[2];
	if (server_pid <= 0)
		return (1);
	printf("ac = %d - server_pid = %d - string : %s\n", ac, server_pid, av[2]);
	int i = 0;
	while (av[2][i])
	{
		send_int(server_pid, av[2][i]);
		i++;
	}
	return (0);
}
