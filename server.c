/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:38:44 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/07 21:44:15 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

s_lclient *lc = NULL;

void	handler(int sig, siginfo_t *sinfo, void *p)
{
	static unsigned int res = 0;
	static unsigned int bit = 0;

	if (sig != SIGUSR1 && sig != SIGUSR2)
		return ;
	if (sig == SIGUSR1)
		res = res + ((unsigned int)1 << bit);
	bit = (bit + 1) % UNIT_SIZE;
	if (!bit)
	{
		ft_printf("%u\n", res);
		res = 0;
	}
	usleep(WAIT_TIME);
	kill(sinfo->si_pid, SIGUSR1);
}


int main()
{
	struct sigaction s;

	ft_printf("server pid %d\n", getpid());
	share_server_pid();
	s.sa_sigaction = handler;
	s.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s, NULL);
	sigaction(SIGUSR2, &s, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
