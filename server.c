/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:38:44 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/11 00:43:04 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_lclient *lc = NULL;

int	print_unicode_char(char *str)
{
	int	i;
	int bytes_rep;

	i = 7;
	bytes_rep = 0;
	while (i >= 0 && *str >> i & 1)
	{
		i--;
		bytes_rep++;
	}
	if (bytes_rep == 0)
		bytes_rep = 1;
	write(1, str, bytes_rep);
	return (bytes_rep);
}

void	print_unicode_str(char *str)
{
	while (*str)
		str = str + print_unicode_char(str);
}

void	allocate_data(t_client *c)
{
	//printf("->(%d)size of data %lu \n", (c->bit / UNIT_SIZE - 1), c->size);
	*((char *)(&(c->size)) + (c->bit / UNIT_SIZE - 1)) = c->res;
	if (c->bit == sizeof(size_t) * 8)
	{
		printf("->(%d)size of data %lu \n", (c->bit / UNIT_SIZE - 1), c->size);
		c->bit = 0;
		c->data = malloc(c->size + 1);
		if (!c->data)
		{
			kill(c->pid, SIGUSR2);
			exit(EXIT_FAILURE);
		}
		c->size = 0;
	}
}

void	get_unit(t_client *c)
{
	//ft_printf("------####%d from client %d | bit = %d\n", c->res, c->pid, c->bit);
	if (c->data != NULL)
	{
		c->data[c->size] = c->res;
		c->size++;
		c->bit = 0;
		if (c->res == 0)
		{
			print_unicode_str(c->data);
			ft_printf("-> From Client %d\n", c->pid);
			remove_client(&lc, c->pid);
			return ;
		}
	}
	else
		allocate_data(c);
	c->res = 0;
}

void	handler(int sig, siginfo_t *sinfo, void *p)
{
	t_client	*c;

	if (sig != SIGUSR1 && sig != SIGUSR2)
		return ;
	c = add_or_find_c(&lc, sinfo->si_pid);
	if (sig == SIGUSR1)
	{
		c->res = c->res + ((char)1 << (c->bit % UNIT_SIZE));
		//ft_printf("received (%d, %d, 1)\n", c->bit + 1, c->pid);
	}else
	{
		//ft_printf("received (%d, %d, 0)\n", c->bit + 1, c->pid);
	}
	c->bit = c->bit + 1;
	//ft_printf("1.Send To %d\n", c->pid);
	kill(c->pid, SIGUSR1);
	usleep(200);
	if (c->bit % UNIT_SIZE == 0)
	{
		get_unit(c);
		//remove_client(&lc, c->pid);
		//print_list(lc);
	}
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
