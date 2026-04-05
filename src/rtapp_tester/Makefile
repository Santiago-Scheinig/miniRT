# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aramos-r <aramos-r@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/15 17:51:38 by sscheini          #+#    #+#              #
#    Updated: 2026/04/04 18:39:44 by aramos-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc

MATHMAINFILE=math_tester.c
LIBRTDIR=../libs/librt/
LIBRTFILE=$(LIBRTDIR)librt.a

MATHHEADERDIR=../libs/librt/include/
MATHHEADERFILE=$(MATHHEADERDIR)rtmth.h

MATH_CFLAGS= -I$(MATHHEADERDIR)

all: math elems

.PHONY: all math elems

TESTNAME=mathtest
math: $(MATHMAINFILE) $(MATHHEADERFILE) $(LIBRTFILE)
	make -C ../../
	@$(CC) $(MATH_CFLAGS) $(MATHMAINFILE) $(LIBRTFILE) -lm -o $(TESTNAME)
	@./$(TESTNAME)
	@rm $(TESTNAME)
	@norminette ../libs/librt/src/rtmth | grep Error || true

ELEMSMAINFILE=elems_tester.c
ELEMSHEADERDIR=../libs/librt/include/rtelm/
ELEMSHEADERFILE=$(ELEMSHEADERDIR)rtelm.h
LIBFTHEADERDIR=../libs/libft/include/

ELEMS_CFLAGS= -I$(ELEMSHEADERDIR) -I$(MATHHEADERDIR) -I$(LIBFTHEADERDIR)

TESTNAME=elemstest
elems: $(ELEMSMAINFILE) $(ELEMSHEADERFILE) $(LIBRTFILE)
	make -C ../../
	@$(CC) $(ELEMS_CFLAGS) $(ELEMSMAINFILE) $(LIBRTFILE) -lm -o $(TESTNAME)
	@./$(TESTNAME)
	@rm $(TESTNAME)
	@norminette ../libs/librt/src/rtelm | grep Error || true

RENDERMAINFILE=render_tester.c
RENDERHEADERDIR=../libs/librt/include/rtapp/
RENDERHEADERFILE=$(RENDERHEADERDIR)rtapp_render.h
LIBFTHEADERDIR=../libs/libft/include/

RENDER_CFLAGS= -I$(RENDERHEADERDIR) -I$(MATHHEADERDIR) -I$(LIBFTHEADERDIR)

TESTNAME=rendertest
render: $(RENDERMAINFILE) $(RENDERHEADERFILE) $(LIBRTFILE)
	make -C ../../
	@$(CC) $(RENDER_CFLAGS) $(RENDERMAINFILE) $(LIBRTFILE) -lm -o $(TESTNAME)
	@./$(TESTNAME)
	@rm $(TESTNAME)
	@norminette ../libs/librt/src/rtapp/rtapp_render | grep Error || true

