/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:11:56 by thi-phng          #+#    #+#             */
/*   Updated: 2021/06/22 12:38:48 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	minus_zero_intp(t_flags *f, const char *s, int *n, int y)
{
	if (y == 0)
	{
		f->i = '0';
		(*n)++;
	}
	if (y == 1)
	{
		f->i = '-';
		(*n)++;
		while (s[*n] == '0')
		{
			f->i = '-';
			(*n)++;
		}
	}
	if (y == 3)
	{
		f->intp = f->intp * 10 + (s[*n] - '0');
		(*n)++;
	}
	return (0);
}

int	get_width_star(t_flags *f, va_list ap, const char *s, int *n)
{
	f->width = f->width * 10 + (s[*n] - '0');
	(*n)++;
	return (0);
}

int	get_star(t_flags *f, va_list ap, const char *s, int *n)
{
	f->width = va_arg(ap, int);
	if (f->width < 0)
	{
		f->i = '-';
		f->width *= -1;
	}
	(*n)++;
	return (0);
}

int	get_intp(t_flags *f, va_list ap, const char *s, int *n)
{
	f->prec = '.';
	(*n)++;
	if (f_find(s[*n], "*"))
	{
		f->intp = va_arg(ap, int);
		if (f->intp < 0)
		{
			f->intp = -1;
			f->prec = 0;
		}
		(*n)++;
	}
	return (0);
}
