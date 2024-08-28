/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:38:44 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/09 20:23:15 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error_happen(pid_t p)
{
	kill(p, SIGUSR2);
	exit(EXIT_FAILURE);
}

void	allocate_data(t_client *c)
{
	*((char *)(&(c->size)) + c->i) = c->res;
	if (c->i == 7)
	{
		c->data = malloc(c->size + 1);
		if (!c->data)
			error_happen(c->pid);
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

	(void)(p);
	if (sinfo->si_pid == 0)
		return ;
	b = ((char)1 << (c.bit % 8)) * (SIGUSR1 / sig);
	c.pid = sinfo->si_pid;
	c.res = c.res + b;
	c.bit = c.bit + 1;
	if (c.bit % 8 == 0)
		get_unit(&c);
	usleep(WAIT_TIME_S);
	if (kill(c.pid, SIGUSR1) == -1)
		error_happen(c.pid);
}

int	main(void)
{
	struct sigaction	s;
	sigset_t			set;

	ft_putnbr((int)getpid());
	write(1, "\n", 1);
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	s.sa_sigaction = handler;
	s.sa_flags = SA_SIGINFO;
	s.sa_mask = set;
	if (sigaction(SIGUSR1, &s, NULL) == -1
		|| sigaction(SIGUSR2, &s, NULL) == -1)
	{
		write(1, "Error\n", 1);
		return (0);
	}
	while (1)
		pause();
	return (0);
}
