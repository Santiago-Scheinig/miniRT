# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/15 17:51:38 by sscheini          #+#    #+#              #
#    Updated: 2026/04/01 17:20:01 by sscheini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
LDFLAGS=-lm

MATHMAINFILE=math_tester.c
MATHDIR=../libs/rtmth
MATHHEADER = -I ../libs/librt/include

.PHONY: all math

math: $(MATHSOURCES) $(MATHMAINFILE)
	@$(CC) $(MATHMAINFILE) ../libs/librt/librt.a $(LDFLAGS) $(MATHHEADER) -o math_tester
	@./math_tester
	@rm math_tester