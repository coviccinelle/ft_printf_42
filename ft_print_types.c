/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_types.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:06:05 by thi-phng          #+#    #+#             */
/*   Updated: 2021/06/22 11:08:10 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa(unsigned int n, char y, char x)
{
	int		ret;
	char	c;
	char	*s;

	s = "0123456789abcdef";
	ret = 0;
	if (n / 16)
		ret += ft_hexa (n / 16, y, x);
	c = s[n % 16];
	if (y == 1)
	{
		if (x == 'X' && f_find(c, "abcdef"))
			c -= 32;
		ret += write (1, &c, 1);
	}
	else
		ret++;
	return (ret);
}

int	ft_hexa_pointeur(unsigned long long int n, char y)
{
	int		ret;
	char	c;
	char	*s;

	s = "0123456789abcdef";
	ret = 0;
	if (n / 16)
		ret += ft_hexa_pointeur (n / 16, y);
	c = s[n % 16];
	if (y == 1)
		ret += write (1, &c, 1);
	else
		ret++;
	return (ret);
}

int	print_p(void	*p, char	y)
{
	unsigned long long	c;
	int					ret;

	c = (unsigned long long)p;
	ret = 0;
	ret += ft_hexa_pointeur (c, y);
	return (ret);
}

void	stock_va_arg(t_flags *f, va_list ap)
{
	f->z.c = 0;
	f->z.u = 0;
	f->z.n = 0;
	f->z.s = "(null)";
	f->z.p = NULL;
	if (f->type == 'c')
		f->z.c = va_arg(ap, int);
	if (f->type == 'x' || f->type == 'X' || f->type == 'u')
		f->z.u = va_arg(ap, unsigned int);
	if (f->type == 'd' || f->type == 'i')
		f->z.n = va_arg(ap, int);
	if (f->type == 's')
		f->z.s = va_arg(ap, char *);
	if (f->type == 'p')
		f->z.p = va_arg(ap, void *);
	if (!f->z.s)
		f->z.s = "(null)";
	return ;
}
