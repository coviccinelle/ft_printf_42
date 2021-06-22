/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 18:18:59 by thi-phng          #+#    #+#             */
/*   Updated: 2021/06/22 11:52:57 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_type
{
	char				c;
	char				*s;
	long int			n;
	void				*p;
	unsigned int		u;
}				t_type;

typedef struct s_flags
{
	char	i;
	int		width;
	char	prec;
	int		intp;
	char	type;
	t_type	z;
}				t_flags;
*/
void	init_flags(t_flags *f)
{
	f->i = 0;
	f->width = 0;
	f->prec = 0;
	f->intp = 0;
	f->type = 0;
	return ;
}
/*
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
*/

/*
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
*/
/*
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
*/
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

/*
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

void	fct_decoupe(va_list ap, struct s_flags *f, int (*h)[5])
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

int	print_type(va_list ap, struct s_flags *f)
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
		while (f_find(s[*n], "0123456789"))
		{
			f->intp = f->intp * 10 + (s[*n] - '0');
			(*n)++;
		}
	}
	return (0);
}
*/

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
