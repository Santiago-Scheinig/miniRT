# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/15 17:51:38 by sscheini          #+#    #+#              #
#    Updated: 2026/04/01 18:00:18 by aramos-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc

NAME=mathtest

MATHMAINFILE=math_tester.c
LIBRTDIR=../libs/librt/
LIBRTFILE=$(LIBRTDIR)librt.a

MATHHEADERDIR=../libs/librt/include/
MATHHEADERFILE=$(MATHHEADERDIR)rtmth.h

LDFLAGS= -I$(MATHHEADERDIR)

math: $(MATHMAINFILE) $(MATHHEADERFILE) $(LIBRTFILE)
	@$(CC) $(LDFLAGS) $(MATHMAINFILE) $(LIBRTFILE) -o $(NAME)
	@./$(NAME)
	@rm $(NAME)
	@norminette ../libs/rtmth | grep Error || yes

$(LIBRTFILE):
	make -C ../../

.PHONY: all math
