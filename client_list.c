/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:15:41 by ayoub             #+#    #+#             */
/*   Updated: 2021/12/10 19:40:15 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_lclient	*find_c_node(t_lclient *lc, pid_t pid)
{
	t_lclient *tmp;

	tmp = lc;
	while (tmp)
	{
		if (tmp->client->pid == pid)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);	
}

// t_client	*find_c(t_lclient *lc, pid_t pid)
// {
// 	t_lclient *tmp;

// 	tmp = find_c_node(lc, pid);
// 	if (!tmp)
// 		return (NULL);
// 	return (tmp->client);
// }

t_client	*add_or_find_c(t_lclient **lc, pid_t pid)
{
	t_client	*c;
	t_lclient	*newc;

	newc = find_c_node(*lc, pid);
	if (newc != NULL)
		return (newc->client);
	c = malloc(sizeof(t_client));
	newc = malloc(sizeof(t_lclient));
	c->pid = pid;
	c->bit = 0;
	c->res = 0;
	c->data = NULL;
	c->size = 0;
	newc->client = c;
	newc->next = NULL;
	if (!(*lc))
		*lc = newc;
	else
	{
		newc->next = *lc;
		*lc = newc;
	}
	return (c);
}

t_client	*get_next_c(t_lclient *lc, pid_t pid)
{
	t_lclient	*c;

	if (!lc)
		return (NULL);
	c = find_c_node(lc, pid);
	if (c->next == NULL)
		return (lc->client);
	return (c->next->client);
}

static void	free_client_node(t_lclient *c)
{
	free(c->client->data);
	free(c->client);
	free(c);
}

void	remove_client(t_lclient **lc, pid_t pid)
{
	t_lclient	*c;
	t_lclient	*prev;

	c = find_c_node(*lc, pid);
	if (!c)
		return ;
	if (c == *lc)
	{
		*lc = c->next;
		free_client_node(c);
		return ;
	}
	prev = *lc;
	while (prev->next != c)
		prev = prev->next;
	prev->next = c->next;
	free_client_node(c);
}

void	print_list(t_lclient *lc)
{
	ft_printf("#####\n");
	while (lc)
	{
		ft_printf("%d\n", lc->client->pid);
		lc = lc->next;
	}
	ft_printf("#####\n");
}
