/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:38:44 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/22 15:39:51 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	allocate_data(t_client *c)
{
	*((char *)(&(c->size)) + c->i) = c->res;
	if (c->i == 7)
	{
		c->data = malloc(c->size + 1);
		if (!c->data)
		{
			kill(c->pid, SIGUSR2);
			exit(EXIT_FAILURE);
		}
		c->i = 0;
	}
	else
		c->i++;
}

void	get_unit(t_client *c)
{
	if (c->data != NULL)
	{
		c->data[c->i] = c->res;
		c->i++;
		if (c->res == 0)
		{
			printf("%lu", c->i);
			write(1, c->data, c->i);
			free(c->data);
			c->data = NULL;
			c->i = 0;
		}
	}
	else
		allocate_data(c);
	c->res = 0;
	c->bit = 0;
}

void	handler(int sig, siginfo_t *sinfo, void *p)
{
	static t_client	c;
	int				b;

	if ((sig != SIGUSR1 && sig != SIGUSR2) || sinfo->si_pid == 0)
		return ;
	b = ((char)1 << (c.bit % 8)) * (SIGUSR1 / sig);
	c.pid = sinfo->si_pid;
	c.res = c.res + b;
	c.bit = c.bit + 1;
	if (c.bit % 8 == 0)
		get_unit(&c);
	usleep(WAIT_TIME);
	kill(c.pid, SIGUSR1);
	usleep(WAIT_TIME);
}

int	main(void)
{
	struct sigaction	s;
	sigset_t			set;

	printf("server pid %d\n", getpid());
	share_server_pid();
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	s.sa_sigaction = handler;
	s.sa_flags = SA_SIGINFO;
	s.sa_mask = set;
	sigaction(SIGUSR1, &s, NULL);
	sigaction(SIGUSR2, &s, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
