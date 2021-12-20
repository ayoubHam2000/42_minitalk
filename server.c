/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:38:44 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/20 21:04:42 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

int	hamming_check(t_client *c)
{
	char	bits[8];
	int		i;

	i = 0;
	while (i < 8)
		bits[i++] = 0;
	return(0);
}

void	collect()
{
	
}

void	get_unit(t_client *c)
{
	c->hammingb[(c->bit / 8) % 7] = c->res;
	if (c->bit % 48 != 0)
		return ;
	if (hamming_check(c) == -1)
		kill(c->pid, SIGUSR2);
	else
		collect();
}

void	handler(int sig, siginfo_t *sinfo, void *p)
{
	static t_lclient	*lc = NULL;
	t_client			*c;
	int					b;

	if ((sig != SIGUSR1 && sig != SIGUSR2) || sinfo->si_pid == 0)
		return ;
	c = add_or_find_c(&lc, sinfo->si_pid);
	b = ((char)1 << (c->bit % UNIT_SIZE)) * (SIGUSR1 / sig);
	c->res = c->res + b;
	c->bit = c->bit + 1;
	usleep(100);
	kill(c->pid, SIGUSR1);
	if (c->bit % UNIT_SIZE == 0)
		get_unit(c);
	usleep(WAIT_TIME);
}


int main()
{
	struct sigaction s;
	sigset_t	set;

	ft_printf("server pid %d\n", getpid());
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
