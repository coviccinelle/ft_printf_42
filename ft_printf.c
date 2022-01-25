/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 18:18:59 by thi-phng          #+#    #+#             */
/*   Updated: 2021/06/22 12:06:25 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_flags(t_flags *f)
{
	f->i = 0;
	f->width = 0;
	f->prec = 0;
	f->intp = 0;
	f->type = 0;
	return ;
}

int	ft_p_flags(struct s_flags *f, char y)
{
	if (f->type == 's' && !(f->prec == '.' && f->intp == 0))
		return (ft_putstr(f->z.s, f->intp, y));
	if (f_find(f->type, "xX") && !(f->prec == '.' && f->intp == 0
			&& f->z.u == 0))
		return (ft_hexa(f->z.u, y, f->type));
	if (f_find(f->type, "di") && !(f->prec == '.' && f->intp == 0
			&& f->z.n == 0))
		return (ft_putnbr(f->z.n, y));
	if (f->type == 'u' && !(f->prec == '.' && f->intp == 0 && f->z.u == 0))
		return (ft_putnbr_unsigned(f->z.u, y));
	if (f->type == 'c')
		return (ft_putchar(f->z.c, y));
	if (f->type == '%')
		return (ft_putchar('%', y));
	if (f->type == 'p' && !(f->prec == '.' && f->z.p == NULL))
		return (print_p(f->z.p, y));
	return (0);
}

int	ft_printf_flags(va_list ap, const char *s, int *n)
{
	t_flags		f;

	init_flags(&f);
	(*n)++;
	while (s[*n] == '0')
		minus_zero_intp(&f, s, n, 0);
	while (s[*n] == '-')
		minus_zero_intp(&f, s, n, 1);
	while (f_find(s[*n], "0123456789"))
		get_width_star(&f, ap, s, n);
	if (f_find(s[*n], "*"))
		get_star(&f, ap, s, n);
	if (s[*n] == '.')
		get_intp(&f, ap, s, n);
	while (f_find(s[*n], "0123456789"))
		minus_zero_intp(&f, s, n, 3);
	if (f_find(s[*n], "cspdiuxX%"))
	{
		f.type = s[*n];
		(*n)++;
		return (print_type(ap, &f));
	}
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list		ap;
	int			n;
	int			ret;

	ret = 0;
	n = 0;
	va_start(ap, s);
	while (s[n])
	{
		if (s[n] != '%')
		{
			ret += write(1, &(s[n]), 1);
			n++;
		}
		if (s[n] == '%')
		{
			ret += ft_printf_flags(ap, s, &n);
		}
	}
	va_end(ap);
	return (ret);
}
