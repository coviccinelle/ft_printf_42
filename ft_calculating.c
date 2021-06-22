/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculating.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:08:30 by thi-phng          #+#    #+#             */
/*   Updated: 2021/06/22 11:11:46 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_largeur_0(t_flags *f, int size)
{
	int		ret;

	ret = 0;
	while (f->intp > size && f->prec == '.')
	{
		ret += write (1, "0", 1);
		f->intp--;
	}
	return (ret);
}

int	ft_largeur(struct s_flags *f, int size, char y)
{
	int		ret;

	ret = 0;
	if (y == 0)
	{
		while (f->width > size && f->i != '-')
		{
			if (f->i == '0' && (f->prec == 0 || f->intp < 0 || f->type == '%'))
				ret += write (1, "0", 1);
			else
				ret += write (1, " ", 1);
			f->width--;
		}
	}
	if (y == 1 && f->type != 's' && f->type != '%')
		ret += ft_largeur_0(f, size);
	if (y == 2)
	{
		while (f->i == '-' && f->width > size)
		{
			ret += write (1, " ", 1);
			f->width--;
		}
	}
	return (ret);
}

int	ft_largeur_pointeur(t_flags	*f, int size, int y)
{
	int	ret;

	ret = 0;
	if (y == 0)
	{
		if (f->i != '0' && f->i != '-')
		{
			while (f->width)
			{
				ret += write (1, " ", 1);
				(f->width)--;
			}
		}
	}
	if (y == 1)
	{
		while (f->intp > size && f->prec == '.')
		{
			ret += write (1, "0", 1);
			f->intp--;
		}
	}
	return (ret);
}

void	fct_decoupe(va_list ap, t_flags *f, int (*h)[5])
{
	(*h)[3] = 0;
	stock_va_arg(f, ap);
	if (f->width < 0)
	{
		f->width *= -1;
		f->i = '-';
	}
	(*h)[4] = 0;
	if (f->type == 'p')
		(*h)[4] = 2;
	(*h)[2] = 0;
	if (f_find(f->type, "di") && f->z.n < 0)
		(*h)[2] = 1;
	(*h)[0] = ft_p_flags(f, 0);
	(*h)[1] = (*h)[0] + (*h)[4];
	if (!f_find(f->type, "s%") && f->prec == '.' && \
			(f->intp + (*h)[2] > (*h)[0] + (*h)[4]))
		(*h)[1] = f->intp + (*h)[2];
}

int	print_type(va_list ap, t_flags *f)
{
	int		h[5];

	fct_decoupe(ap, f, &h);
	if (f_find(f->type, "di") && f->z.n < 0 && f->i == '0' && \
			!(f->prec == '.'))
	{
		h[3] += write(1, "-", 1);
		f->z.n *= -1;
	}
	h[3] += ft_largeur(f, h[1], 0);
	if (f->type == 'p')
		h[3] += ft_putstr("0x", 0, 1);
	if (f_find(f->type, "di") && f->z.n < 0 && (f->prec == '.'))
	{
		h[3] += write(1, "-", 1);
		h[0]--;
		f->z.n *= -1;
	}
	h[3] += ft_largeur(f, h[0], 1);
	h[3] += ft_p_flags(f, 1);
	h[3] += ft_largeur(f, h[1], 2);
	return (h[3]);
}
