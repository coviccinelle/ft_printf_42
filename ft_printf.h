/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 12:47:05 by thi-phng          #+#    #+#             */
/*   Updated: 2021/06/22 11:45:54 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_type
{
	char			c;
	char			*s;
	long int		n;
	void			*p;
	unsigned int	u;
}				t_type;

typedef struct s_flags
{
	char		i;
	int			width;
	char		prec;
	int			intp;
	char		type;
	t_type		z;
}				t_flags;

void	init_flags(t_flags *f);
int		ft_printf(const char *s, ...);
int		ft_printf_flags(va_list ap, const char *s, int *n);
int		ft_p_flags(t_flags *f, char y);
//size = ft_p_flags;

// flags //
int		minus_zero_intp(t_flags *f, const char *s, int *n, int y);
int		get_width_star(t_flags *f, va_list ap, const char *s, int *n);
int		get_star(t_flags *f, va_list ap, const char *s, int *n);
int		get_intp(t_flags *f, va_list ap, const char *s, int *n);

//    calculating   //
int		ft_largeur(t_flags *f, int	size, char y);
int		ft_largeur_0(t_flags *f, int size);
int		ft_largeur_pointeur(t_flags	*f, int size, int y);
int		print_type(va_list ap, t_flags *f);
void	fct_decoupe(va_list ap, t_flags *f, int (*h)[5]);
// NOTES :
//	h[0] = (int) size;
//	h[1] = (int) largeur;
//	h[2] = (int) neg;
//	h[3] = (int) ret;
//	h[4] = (int) m;

// print types //
int		ft_hexa(unsigned int n, char y, char x);
int		ft_hexa_pointeur(unsigned long long int n, char y);
int		print_p(void *p, char y);
void	stock_va_arg(t_flags *f, va_list ap);

//    utils   //
char	f_find(char c, char *s);
int		ft_putnbr_unsigned(unsigned int n, char y);
int		ft_putnbr(long int n, char y);
int		ft_putstr(char *s, int n, char y);
int		ft_putchar(char c, char y);

// maybe

#endif
