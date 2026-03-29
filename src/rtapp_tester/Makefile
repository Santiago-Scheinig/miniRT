# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/15 17:51:38 by sscheini          #+#    #+#              #
#    Updated: 2026/03/29 17:04:39 by aramos-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
MATHMAINFILE=math_tester.c
MATHDIR=../libs/rtmth
MATHSOURCES := $(shell find $(MATHDIR) -name '*.c')
MATHHEADER = -I../../include

math: $(MATHSOURCES) $(MATHMAINFILE)
	@$(CC) $(MATHSOURCES) $(MATHMAINFILE) $(MATHHEADER) -o math_tester
	@./math_tester
	@rm math_tester