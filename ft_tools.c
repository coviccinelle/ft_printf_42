/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:03:14 by thi-phng          #+#    #+#             */
/*   Updated: 2021/06/22 11:25:03 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	f_find(char	c, char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (c);
		i++;
	}
	return (0);
}

int	ft_putchar(char	c, char y)
{
	if (y == 1)
		write (1, &c, 1);
	return (1);
}

int	ft_putnbr_unsigned(unsigned int n, char y)
{
	int		ret;
	char	c;

	ret = 0;
	if (n / 10)
		ret += ft_putnbr_unsigned(n / 10, y);
	c = n % 10 + '0';
	if (y == 1)
		ret += write(1, &c, 1);
	else
		ret++;
	return (ret);
}

int	ft_putnbr(long int n, char y)
{
	int		ret;
	char	c;

	ret = 0;
	if (n < 0)
	{
		if (y == 1)
			ret += write (1, "-", 1);
		else
			ret++;
		n *= -1;
	}
	if (n / 10)
		ret += ft_putnbr (n / 10, y);
	c = n % 10 + '0';
	if (y == 1)
		ret += write(1, &c, 1);
	else
		ret++;
	return (ret);
}

int	ft_putstr(char *s, int n, char y)
{
	int		ret;

	ret = 0;
	while (s[ret] && (ret < n || n == 0 || n == -1))
	{
		if (y == 1)
			ret += write (1, &s[ret], 1);
		else
			ret += 1;
	}
	return (ret);
}
