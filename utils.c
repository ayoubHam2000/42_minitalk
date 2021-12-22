/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:50:11 by ayoub             #+#    #+#             */
/*   Updated: 2021/12/22 16:17:02 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#define MAX_ULONG_DIV_10 1844674407370955161U

static int	is_blank(char c)
{
	if (c == ' ' || c == '\f'
		|| c == '\v' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int					signe;
	unsigned long long	res;

	while (is_blank(*str))
		str++;
	signe = 1;
	if (*str == '-')
		signe = -1;
	if (*str == '+' || *str == '-')
		str++;
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (res >= MAX_ULONG_DIV_10 && (*str - '0') > 5)
		{
			if (signe < 0)
				return (0);
			if (signe > 0)
				return (-1);
		}
		res = res * 10;
		res = res + (*str - '0');
		str++;
	}
	return (res * signe);
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		nb = nb % 10;
	}
	if (nb < 10)
		ft_putchar(nb + 48);
}
