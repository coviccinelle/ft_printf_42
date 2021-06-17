/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 18:18:59 by thi-phng          #+#    #+#             */
/*   Updated: 2021/06/17 14:46:04 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

typedef struct	s_type
{
	char	c;
	char	*s;
	long int	n;
	void	*p;
	unsigned int		u;
}				t_type;


typedef struct	s_flags
{
	char	i;
	int		width;
	char	precision;
	int		intp;
	char	type;
	t_type		z;
}				t_flags;

void	init_flags(t_flags *f)
{
	f->i = 0;
	f->width = 0;
	f->precision = 0;
	f->intp = 0;
	f->type = 0;
	return ;
}

char	ft_find(char	c, char *s)
{
	int		i;

	i = 0;
	while(s[i])
	{
		if(c == s[i])
			return(c);
		i++;
	}
	return(0);
}

int		ft_putchar(char	c, char y)
{
	if(y == 1)
		write(1, &c, 1);
	return(1);
}

int		ft_putnbr_unsigned(unsigned int n, char y)
{
	int		ret;
	char	c;
	
	ret = 0;
	if(n / 10)
		ret += ft_putnbr_unsigned(n / 10, y);
	c = n % 10 + '0';
	if(y == 1)
		ret += write(1, &c, 1);
	else
		ret++;
	return(ret);
}

int		ft_putnbr(long int n, char y)
{
	int		ret;
	char	c;
	
	ret = 0;
	if(n < 0)
	{
		if(y == 1)
			ret += write(1, "-", 1);
		else
			ret++;
		n *= -1;
	}
	if(n / 10)
		ret += ft_putnbr(n / 10, y);
	c = n % 10 + '0';
	if(y == 1)
		ret += write(1, &c, 1);
	else
		ret++;
	return(ret);
}

int		ft_hexa(unsigned int n, char y, char x)
{
	int		ret;
	char	c;
	char	*s;
	
	s = "0123456789abcdef";
	ret = 0;
	if(n / 16)
		ret += ft_hexa(n / 16, y, x);
	c = s[n % 16];
	if(y == 1)
	{
		if(x == 'X' && ft_find(c, "abcdef"))
			c -= 32;
		ret += write(1, &c, 1);
	}
	else
		ret++;
	return(ret);
}


int	ft_hexa_pointeur(unsigned long long int n, char y)
{
	int		ret;
	char	c;
	char	*s;
	
	s = "0123456789abcdef";
	ret = 0;
	if(n / 16)
		ret += ft_hexa_pointeur(n / 16, y);
	c = s[n % 16];
	if(y == 1)
		ret += write(1, &c, 1);
	else
		ret++;
	return(ret);
}

int		print_p(void	*p, char	y)
{
	unsigned long long	c;
	int					ret;

	c = (unsigned long long)p;
	ret = 0;
	ret += ft_hexa_pointeur(c, y);
	return(ret);
}


int		ft_putstr(char *s, int n, char y)
{
	int		ret;

	ret = 0;
	while(s[ret] && (ret < n || n == 0 || n == -1))
	{
		if(y == 1)
			ret += write(1, &s[ret], 1);
		else
			ret += 1;
	}
	return(ret);
}


int		ft_p_flags(struct s_flags *f, char y)
{
	if(f->type == 's' && !(f->precision == '.' && f->intp == 0))
		return(ft_putstr(f->z.s, f->intp, y));
	if(ft_find(f->type, "xX") && !(f->precision == '.' && f->intp == 0 && f->z.u == 0))
		return(ft_hexa(f->z.u, y, f->type));
	if(ft_find(f->type, "di") && !(f->precision == '.' && f->intp == 0 && f->z.n == 0))
		return(ft_putnbr(f->z.n, y));
	if(f->type == 'u' && !(f->precision == '.' && f->intp == 0 && f->z.u == 0))
		return(ft_putnbr_unsigned(f->z.u, y));
	if(f->type == 'c')
		return(ft_putchar(f->z.c, y));
	if(f->type == '%')
		return(ft_putchar('%', y));
	if(f->type == 'p' && !(f->precision == '.' && f->z.p == NULL))
		return(print_p(f->z.p, y));
	return(0);
}

int		ft_largeur1_0(t_flags *f, int size)
{
	int		ret;

	ret = 0;
	while(f->intp > size && f->precision == '.')
	{
		ret += write(1, "0", 1);
		f->intp--;
	}
	return (ret);
}


int		ft_largeur(struct s_flags *f, int size, char y)
{
	int		ret;

	ret = 0;
	if(y == 0)
	{
		while(f->width > size && f->i != '-')
		{
			if((f->i == '0') && ((f->precision == 0 || f->intp < 0 || f->type == '%')))
				ret += write(1, "0", 1);
			else
				ret += write(1, " ", 1);
			f->width--;
		}
	}
	if(y == 1 && f->type != 's' && f->type != '%')
		ret += ft_largeur1_0(f, size);
	if(y == 2)
	{
		while(f->i == '-' && f->width > size)
		{
			ret += write(1, " ", 1);
			f->width--;
		}
	}
	return(ret);
}

int			ft_largeur_pointeur(t_flags	*f)
{
	int		ret;

	ret = 0;
	if(f->i != '0' && f->i != '-')
	{
		while(f->width)
		{
			ret += write(1, " ", 1);
			(f->width)--;
		}
	}
	return(ret);

}

void		stock_va_arg(t_flags *f, va_list ap)
{
	f->z.c = (f->type == 'c')? va_arg(ap, int) : 0;
	f->z.u = (f->type == 'x' || f->type == 'X' || f->type == 'u')? va_arg(ap, unsigned int) : 0;
	f->z.n = (f->type == 'd' || f->type == 'i')? va_arg(ap, int) : 0;
	f->z.s = (f->type == 's')? va_arg(ap, char*) : "(null)";
	f->z.p = (f->type == 'p')? va_arg(ap, void*) : NULL;
	if(!f->z.s)
		f->z.s = "(null)";
	return ;
}


int		print_type(va_list ap, struct s_flags *f)
{
	stock_va_arg(f, ap);
	int		size;
	int		largeur;
	int		neg;
	int		ret;
	int		m;

	if(f->width < 0)
	{
		f->width *= -1;
		f->i = '-';
	}

	m = (f->type == 'p')? 2 : 0;
	neg = ((f->type == 'd' || f->type == 'i') && f->z.n < 0)? 1 : 0;
	size = ft_p_flags(f, 0);
	largeur = (f->type != 's' && f->type != '%' && (f->precision == '.' && (f->intp + neg > size + m)))? f->intp + neg : size + m;


	ret = 0;
	if(ft_find(f->type, "di") && f->z.n < 0 && f->i== '0' && !(f->precision == '.'))
	{
		ret += write(1, "-", 1);
		size--;
		f->z.n *= -1;
	}
	ret += ft_largeur(f, largeur, 0);
	if(f->type == 'p')
		ret += ft_putstr("0x", 0, 1);
	if(ft_find(f->type, "di") && f->z.n < 0 && (f->precision == '.'))
	{
		ret += write(1, "-", 1);
		size--;
		f->z.n *= -1;
	}
	ret += ft_largeur(f, size, 1);
	ret += ft_p_flags(f, 1);
	ret += ft_largeur(f, largeur, 2);
	return(ret);
}


int		ft_printf_flags(va_list ap, const char *s, int *n)
{
	struct	s_flags		f;

	init_flags(&f);
	(*n)++;
	while(s[*n] == '0')
	{
		f.i = '0';
		(*n)++;
	}
	while(s[*n] == '-')
	{
		f.i = '-';
		(*n)++;
		while(s[*n] == '0')
		{
			f.i = '-';
			(*n)++;
		}
	}
	while(ft_find(s[*n], "0123456789"))
	{
		f.width = f.width * 10 + (s[*n] - '0');
		(*n)++;
	}
	if(ft_find(s[*n], "*"))
	{
		f.width = va_arg(ap, int);
		if(f.width < 0)
		{
			f.i = '-';
			f.width *= -1;
		}
		(*n)++;
	}
	if(s[*n] == '.')
	{
		f.precision = '.';
		(*n)++;
		if(ft_find(s[*n], "*"))
		{
			f.intp = va_arg(ap, int);
			if(f.intp < 0)
			{
				f.intp = -1;
				f.precision = 0;
			}
			(*n)++;
		}
	}
	while(ft_find(s[*n], "0123456789"))
	{
		f.intp = f.intp * 10 + (s[*n] - '0');
		(*n)++;
	}
	if(ft_find(s[*n], "cspdiuxX%"))
	{
		f.type = s[*n];
		(*n)++;
		return(print_type(ap, &f));
	}
	return(0);
}

int		ft_printf(const char *s, ...)
{
	va_list		ap;
	int			n;
	int			ret;

	ret = 0;
	n = 0;
	va_start(ap, s);
	while(s[n])
	{
		if(s[n] != '%')
		{
			ret += write(1, &(s[n]), 1);
			n++;
		}
		if(s[n] == '%')
		{
			ret += ft_printf_flags(ap, s, &n);
		}
	}
	va_end(ap);
	return(ret);
}
