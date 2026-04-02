# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/15 17:51:38 by sscheini          #+#    #+#              #
#    Updated: 2026/04/02 14:53:49 by aramos-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc

NAME=mathtest

MATHMAINFILE=math_tester.c
LIBRTDIR=../libs/librt/
LIBRTFILE=$(LIBRTDIR)librt.a

MATHHEADERDIR=../libs/librt/include/
MATHHEADERFILE=$(MATHHEADERDIR)rtmth.h

MATH_CFLAGS= -I$(MATHHEADERDIR)

all: math elems

$(LIBRTFILE):
	make -C ../../

.PHONY: all math elems

math: $(MATHMAINFILE) $(MATHHEADERFILE) $(LIBRTFILE)
	@$(CC) $(MATH_CFLAGS) $(MATHMAINFILE) $(LIBRTFILE) -lm -o $(NAME)
	@./$(NAME)
	@rm $(NAME)
	@norminette ../libs/librt/src/rtmth | grep Error || true

ELEMSMAINFILE=elems_tester.c
ELEMSHEADERDIR=../libs/librt/include/rtelm/
ELEMSHEADERFILE=$(ELEMSHEADERDIR)rtelm.h
LIBFTHEADERDIR=../libs/libft/include/

ELEMS_CFLAGS= -I$(ELEMSHEADERDIR) -I$(MATHHEADERDIR) -I$(LIBFTHEADERDIR)

elems: $(ELEMSMAINFILE) $(ELEMSHEADERFILE) $(LIBRTFILE)
	@$(CC) $(ELEMS_CFLAGS) $(ELEMSMAINFILE) $(LIBRTFILE) -lm -o $(NAME)
	@./$(NAME)
	@rm $(NAME)
	@norminette ../libs/librt/src/rtelm | grep Error || true
