/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 12:47:05 by thi-phng          #+#    #+#             */
/*   Updated: 2021/06/11 15:50:17 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>

typedef struct	s_type
{
	char			c;
	char			*s;
	long int		n;
	void			*p;
	unsigned int	u;
}				t_type;

typedef struct	s_flags
{
	char		i;
	int			width;
	char		precision;
	int			raional_num;
	char		type;
	t_type		z;
}				t_flags;



//    main printf //

int			ft_printf(const char *s, ...);
int			ft_printf_flags(va_list ap, const char *s, int *n);
int			print_type(va_list ap, t_flags *f);
int			ft_p_flags(t_flags *f, char y);

//size = ft_p_flags;


//    calculating   //
int		ft_largeur(t_flags *f, int	size, char y);
int		ft_largeur_pointeur(t_flags *f, int size);
void	stock_va_arg(t_flags *f, va_list ap);

// print types //

int		ft_hexa(unsigned int n, char y, char x);
int		ft_hexa_pointeur(unsigned long long int n, char y);
int		print_p(t_flags *f, void *p, char y);
int		ft_putchar(char c, char y);
int		ft_putnbr_unisgned(unsigned int n, char y);
int		ft_putnbr(long int n, char y);
int		ft_putstr(char *s, int n, char y);



//    utils   //
void	init_flags(t_flags *f);
char	ft_find(char c, char *s);


// maybe

#endif
