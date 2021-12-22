/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:38:44 by aben-ham          #+#    #+#             */
/*   Updated: 2021/12/22 13:06:06 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

void	allocate_data(t_client *c, char *message)
{
	t_lclient	*tmp;

	//printf("->(%zu)size of data %zu \n", c->i, c->size);
	*((char *)(&(c->size)) + c->i) = message[(c->i) % 7];
	if (c->i == 7)
	{
		//printf("size of data %lu\n", c->size);
		c->data = malloc(c->size + 1);
		if (!c->data)
			exit(EXIT_FAILURE);
	}	
}

void	collect(t_client *c, char *message)
{
	int	i;

	while (1)
	{
		if (c->i < 8)
		{
			allocate_data(c, message);
		}
		else
		{
			//printf("->(%zu) => %c\n", c->i, message[(c->i) % 7]);
			c->data[c->i - 8] = message[(c->i) % 7];
			//write(1, &message[(c->i) % 7], 1);
			if (!message[(c->i) % 7])
			{
				printf("client %d : \n", c->pid);
				print_unicode_str(c->data);
				write(1, "\n", 1);
				return ;
			}
		}
		c->i++;
		if ((c->i) % 7 == 0)
			break ;
	}
}

void	get_unit(t_client *c)
{
	char	message[7];

	c->hammingb[c->bit / 8 - 1] = c->res;
	if (c->bit % 64 == 0)
	{
		if (hammingc(c->hammingb))
		{
			//printf("%lu Error From %d\n", get_time(), c->pid);
			kill(c->pid, SIGUSR2);
		}
		else
		{	
			kill(c->pid, SIGUSR1);
			extract_from_hamming(message, c->hammingb);
			collect(c, message);
		}
		bezero(c->hammingb, 8);
	}
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
	//printf("%d(%d) ", c->bit, SIGUSR1 / sig);
	c->res = c->res + b;
	c->bit = c->bit + 1;
	usleep(100);
	if (c->bit % 64 != 0)
		kill(c->pid, SIGUSR1);
	if (c->bit % UNIT_SIZE == 0)
	{
		get_unit(c);
		c->bit = (c->bit) % 64;
		c->res = 0;
	}
	usleep(WAIT_TIME);
}


int main()
{
	struct sigaction s;
	sigset_t	set;

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
