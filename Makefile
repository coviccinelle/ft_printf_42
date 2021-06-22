# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 10:17:28 by thi-phng          #+#    #+#              #
#    Updated: 2021/06/22 11:27:01 by thi-phng         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

CLAGS		= -Wall -Wextra -Werror

RM			= rm -rf

CC			= gcc

SRCDIR		= ft_printf.c \
			  ft_calculating.c \
			  ft_flags.c \
			  ft_print_types.c \
			  ft_tools.c \


OBJS		= $(SRCDIR:.c=.o)

%.o : %.c
			$(CC) $(CFLAGS) -c $<

all:		$(NAME)

$(NAME) :	$(OBJS)
	ar rcs $(NAME) $(OBJS)

test:
	$(CC) $(CFLAGS) ft_printf.c && ./aout

clean:
	$(RM) *.o

fclean:		clean
	$(RM) $(NAME)

re:			fclean $(NAME)
