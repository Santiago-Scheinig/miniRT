# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/15 17:51:38 by sscheini          #+#    #+#              #
#    Updated: 2026/04/01 18:06:53 by sscheini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
LDFLAGS=-lm

MATHMAINFILE=math_tester.c
MATHHEADER = -I ../libs/librt/include

.PHONY: all math

math: $(MATHSOURCES) $(MATHMAINFILE)
	@$(CC) $(MATHMAINFILE) ../libs/librt/librt.a $(LDFLAGS) $(MATHHEADER) -o math_tester
	@./math_tester
	@rm math_tester