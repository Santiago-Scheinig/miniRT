CC = cc

# Lib paths
LIBFTDIR = ../../libs/libft/
LIBFT = $(LIBFTDIR)libft.a

LIBRTDIR = ../../libs/librt/
LIBRT = $(LIBRTDIR)librt.a

# Headers
MATHHEADERDIR = ../../libs/librt/include/
LIBFTHEADERDIR = ../../libs/libft/include/
REDERHEADERDIR = ../../include

# ================== FLAGS ==================
MATH_CFLAGS = -I$(MATHHEADERDIR)
ELEMS_CFLAGS = -I$(MATHHEADERDIR) -I$(LIBFTHEADERDIR)
RENDER_CFLAGS = -I$(MATHHEADERDIR) -I$(LIBFTHEADERDIR) -I$(REDERHEADERDIR)

# ================== TARGETS ==================
.PHONY: all math elems render rtapp

all: math elems render

rtapp:
	@make -C ../../

# ================== MATH ==================
MATHMAIN = math_tester.c
MATH_BIN = mathtest

math: rtapp $(MATHMAIN) $(LIBFT) $(LIBRT)
	@$(CC) $(MATH_CFLAGS) $(MATHMAIN) $(LIBRT) $(LIBFT) -lm -o $(MATH_BIN)
	@./$(MATH_BIN)
	@rm -f $(MATH_BIN)
#	@norminette ../../libs/librt/src/rtmth | grep Error || true

# ================== ELEMS ==================
ELEMSMAIN = elems_tester.c
ELEMS_BIN = elemstest

elems: rtapp $(ELEMSMAIN) $(LIBFT) $(LIBRT)
	@$(CC) $(ELEMS_CFLAGS) $(ELEMSMAIN) $(LIBRT) $(LIBFT) -lm -o $(ELEMS_BIN)
	@./$(ELEMS_BIN)
	@rm -f $(ELEMS_BIN)
#	@norminette ../../libs/librt/src/rtelm | grep Error || true

# ================== RENDER ==================
RENDERMAIN = render_tester.c
RENDER_BIN = rendertest

render: rtapp $(RENDERMAIN) $(LIBFT) $(LIBRT)
	@$(CC) $(RENDER_CFLAGS) $(RENDERMAIN) $(LIBRT) $(LIBFT) ../rtapp/render/tile_queue.c -lm -o $(RENDER_BIN)
	@./$(RENDER_BIN)
	@rm -f $(RENDER_BIN)
#	@norminette ../rtapp/render | grep Error || true
