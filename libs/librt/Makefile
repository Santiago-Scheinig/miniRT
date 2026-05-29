# --------------------------------- Makefile Main ---------------------------------- #

SRC		=	$(SRCDIR)$(ELMDIR)camera.c								\
			$(SRCDIR)$(ELMDIR)plane/plane.c							\
			$(SRCDIR)$(ELMDIR)sphere/sphere.c						\
			$(SRCDIR)$(ELMDIR)cylinder/cylinder.c					\
			$(SRCDIR)$(ELMDIR)cylinder/cylinder_utils.c				\
			$(SRCDIR)$(ELMDIR)light/lights.c						\
			$(SRCDIR)$(ELMDIR)utils/build_utils.c					\
			$(SRCDIR)$(MTHDIR)matrix/mat4.c							\
			$(SRCDIR)$(MTHDIR)matrix/mat4_inverse.c					\
			$(SRCDIR)$(MTHDIR)matrix/mat4_transforms.c				\
			$(SRCDIR)$(MTHDIR)equations/quadratic.c					\
			$(SRCDIR)$(MTHDIR)equations/colors.c					\
			$(SRCDIR)$(MTHDIR)raytracing/ray.c						\
			$(SRCDIR)$(MTHDIR)raytracing/vector_mat4.c				\
			$(SRCDIR)$(MTHDIR)vector/vector.c						\
			$(SRCDIR)$(MTHDIR)vector/vector_vector.c				\
			$(SRCDIR)$(MTHDIR)vector/vector_scalar.c				\
			$(SRCDIR)$(MLXDIR)window.c								\
			$(SRCDIR)$(ERRDIR)object_del.c							\

BSRC	=	$(filter-out											\
			$(SRCDIR)$(ELMDIR)light/lights.c						\
			$(SRCDIR)$(ELMDIR)cylinder/cylinder.c					\
			$(SRCDIR)$(ELMDIR)sphere/sphere.c						\
			$(SRCDIR)$(ELMDIR)plane/plane.c							\
			$(SRCDIR)$(ERRDIR)object_del.c,							\
			$(SRC))													\
			$(SRCDIR)$(ELMDIR)cone/cone_bonus.c						\
			$(SRCDIR)$(ELMDIR)cone/cone_utils_bonus.c				\
			$(SRCDIR)$(ELMDIR)cylinder/cylinder_bonus.c				\
			$(SRCDIR)$(ELMDIR)cylinder/cylinder_utils.c				\
			$(SRCDIR)$(ELMDIR)hyperboloid/hyperboloid_bonus.c		\
			$(SRCDIR)$(ELMDIR)hyperboloid/hyperboloid_utils_bonus.c	\
			$(SRCDIR)$(ELMDIR)paraboloid/paraboloid_bonus.c			\
			$(SRCDIR)$(ELMDIR)paraboloid/paraboloid_utils_bonus.c	\
			$(SRCDIR)$(ELMDIR)plane/plane_bonus.c					\
			$(SRCDIR)$(ELMDIR)sphere/sphere_bonus.c					\
			$(SRCDIR)$(ELMDIR)light/lights_bonus.c					\
			$(SRCDIR)$(ELMDIR)utils/build_utils_bonus.c				\
			$(SRCDIR)$(ERRDIR)object_del_bonus.c					\

SRCDIR	=	src/
OBJDIR	=	obj/
ELMDIR	=	rtelm/
ERRDIR	=	rterr/
MLXDIR	=	rtmlx/
MTHDIR	=	rtmth/

NAME	=	librt.a
BONUS	=	librt_bonus.a

CC		=	cc
EXTRA_FLAGS	?=	-Wno-error=incompatible-pointer-types
CFLAGS	=	-g -Wall -Werror -Wextra $(EXTRA_FLAGS) -I include/ -I libs/libft/include -I libs/minilibx -D W_HEIGHT=$(W_HEIGHT) -D W_WIDTH=$(W_WIDTH)

W_WIDTH ?= 1920
W_HEIGHT ?= 1080

# --------------------------- Makefile Object Compilation -------------------------- #

OBJ			=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
BONUS_SRC	=	$(BSRC)
BOBJ		=	$(BONUS_SRC:$(SRCDIR)%.c=$(OBJDIR)bonus/%.o)

# ------------------------------- Makefile Cosmetics ------------------------------- #

CNAME			=	Librt
CBONUS			=	#- Name of the bonus library with first letter in caps.		-#
COLOUR_GREEN	=	\033[0;32m
COLOUR_RED		=	\033[0;31m
COLOUR_BLUE		=	\033[0;34m
COLOUR_CIAN		=	\033[0;35m
COLOUR_END		=	\033[0m

# --------------------------------- Makefile Body ---------------------------------- #

.PHONY: all clean fclean re libft minilibx minilibx_fclean

all: libft minilibx $(NAME)

libft:
	@$(MAKE) -s -C libs/libft

minilibx:
	@if [ ! -f libs/minilibx/libmlx_Linux.a ]; then \
		printf "$(COLOUR_BLUE)[i] MiniLibX - Object compilation:\n\t$(COLOUR_GREEN)[⚙] " && \
		(while true; do printf '.'; sleep 0.4; done) & \
		SPIN_PID=$$!; \
		cd libs/minilibx && ./configure > /dev/null 2>&1 && \
		$(MAKE) -C libs/minilibx --no-print-directory > /dev/null 2>&1; \
		kill $$SPIN_PID 2>/dev/null; \
		wait $$SPIN_PID 2>/dev/null; \
		printf "\033[2K\r\t$(COLOUR_CIAN)[OK] Library compiled successfully.\n\n$(COLOUR_END)"; \
	fi

#- Creates $(OBJDIR) and all required subdirectories.							-#
$(OBJDIR):
	@printf "$(COLOUR_BLUE)[i] $(CNAME) - Object compilation:\n"
	@mkdir -p $@$(MTHDIR)matrix/
	@mkdir -p $@$(MTHDIR)equations/
	@mkdir -p $@$(MTHDIR)raytracing/
	@mkdir -p $@$(MTHDIR)vector/
	@mkdir -p $@$(ELMDIR)
	@mkdir -p $@$(ELMDIR)cylinder/
	@mkdir -p $@$(ELMDIR)sphere/
	@mkdir -p $@$(ELMDIR)plane/
	@mkdir -p $@$(ELMDIR)light/
	@mkdir -p $@$(ELMDIR)utils/
	@mkdir -p $@$(ERRDIR)
	@mkdir -p $@$(MLXDIR)

#- Compiles each %.c source into its respective %.o								-#
$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\r\033[2K\t$(COLOUR_GREEN)[⚙] $@ created."

$(OBJDIR)bonus/%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -D BONUS=1 -c $< -o $@
	@printf "\r\033[2K\t$(COLOUR_GREEN)[⚙] $@ created."

#- Compiles the $(NAME) static library.											-#
$(NAME): $(OBJDIR) $(OBJ)
	@ar rcs $(NAME) $(OBJ) $(LIBDIR)
	@printf "\r\033[2K\t$(COLOUR_CIAN)[OK] Library compiled successfully.\n\n"

bonus: libft minilibx $(BONUS)

$(BONUS): $(OBJDIR) $(BOBJ)
	@ar rcs $(BONUS) $(BOBJ)
	@printf "\r\033[2K\t$(COLOUR_CIAN)[OK] Bonus library compiled successfully.\n\n"

#- Removes every object inside $(OBJDIR) and the directory itself.					-#
clean:
	@make clean -C libs/libft
	@if [ -d $(OBJDIR) ]; then \
		rm -rf $(OBJDIR); \
		printf "$(COLOUR_BLUE)[i] $(CNAME) - Object cleaning complete. \n$(COLOUR_END)\n"; \
	fi

#- Cleans minilibx build artifacts.												-#
minilibx_fclean:
	@if [ -f libs/minilibx/libmlx_Linux.a ]; then \
		$(MAKE) clean -C libs/minilibx --no-print-directory > /dev/null 2>&1; \
		printf "$(COLOUR_RED)[X] MiniLibX - Files removed.\n\n"; \
	fi

#- Removes all generated files including the final library.						-#
fclean: minilibx_fclean clean
	@make fclean -C libs/libft
	@if [ -f $(NAME) ] || [ -f $(BONUS) ]; then \
		rm -f $(NAME) $(BONUS); \
		echo "$(COLOUR_RED)[X] $(CNAME) - Files removed.\n$(COLOUR_END)"; \
	fi

#- Rebuilds everything from scratch.											-#
re: fclean all