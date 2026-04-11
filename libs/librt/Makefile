# --------------------------------- Makefile Main ---------------------------------- #

SRC		=	$(SRCDIR)$(ELMDIR)plane.c									\
			$(SRCDIR)$(ELMDIR)sphere.c									\
			$(SRCDIR)$(ELMDIR)cylinder.c								\
			$(SRCDIR)$(ELMDIR)cylinder_intersection.c					\
			$(SRCDIR)$(ELMDIR)ambient_light.c							\
			$(SRCDIR)$(ELMDIR)camera.c									\
			$(SRCDIR)$(ELMDIR)light.c									\
			$(SRCDIR)$(ELMDIR)mat4_utils.c								\
			$(SRCDIR)$(MTHDIR)matrix/mat4.c								\
			$(SRCDIR)$(MTHDIR)matrix/mat4_inverse.c						\
			$(SRCDIR)$(MTHDIR)matrix/mat4_transforms.c					\
			$(SRCDIR)$(MTHDIR)equations/quadratic.c						\
			$(SRCDIR)$(MTHDIR)raytracing/ray.c							\
			$(SRCDIR)$(MTHDIR)raytracing/vector_mat4.c					\
			$(SRCDIR)$(MTHDIR)vector/vector.c							\
			$(SRCDIR)$(MTHDIR)vector/vector_vector.c					\
			$(SRCDIR)$(MTHDIR)vector/vector_scalar.c					\
			$(SRCDIR)$(ERRDIR)object_del.c								\

BSRC	=	#- *_bonus.c															-#

SRCDIR	=	src/
OBJDIR	=	obj/
APPDIR	=	rtapp/
ELMDIR	=	rtelm/
ERRDIR	=	rterr/
MLXDIR	=	rtmlx/
MTHDIR	=	rtmth/

NAME	=	librt.a
BONUS	=	#- The name of the bonus final library.									-#

CC		=	cc
CFLAGS	=	-g -Wall -Werror -Wextra -I include/ -I include/rtelm -I ../libft/include

# --------------------------- Makefile Object Compilation -------------------------- #

OBJ		=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
BOBJ	=	$(BSRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

# ------------------------------- Makefile Cosmetics ------------------------------- #

CNAME			=	Librt
CBONUS			=	#-Name of the final bonus program with first letter in caps.	-#
COLOUR_GREEN	=	\033[0;32m
COLOUR_RED		=	\033[0;31m
COLOUR_BLUE		=	\033[0;34m
COLOUR_CIAN		=	\033[0;35m
COLOUR_END		=	\033[0m

# --------------------------------- Makefile Body ---------------------------------- #

.PHONY: all msg clean fclean re

all: $(NAME)

#- Creates a directory named $(OBJDIR).												-#
$(OBJDIR):
	@echo "$(COLOUR_BLUE)[i] $(CNAME) - Object compilation:"
	@mkdir -p $@$(MTHDIR)equations/
	@mkdir -p $@$(MTHDIR)matrix/
	@mkdir -p $@$(MTHDIR)raytracing/
	@mkdir -p $@$(MTHDIR)vector/
	@mkdir -p $@$(ELMDIR)
	@mkdir -p $@$(ERRDIR)
	@mkdir -p $@$(MLXDIR)

#
#- Compiles each %(generic).c source into its respective %(generic).o				-#
$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\r\033[2K\t$(COLOUR_GREEN)[⚙] $@ created."
#
#- Complies the $(NAME) library.													-#
$(NAME): $(OBJDIR) $(OBJ)
	@ar rcs $(NAME) $(OBJ) $(LIBDIR)
	@printf "\r\033[2K\t$(COLOUR_CIAN)[OK] Library compiled successfully.\n\n"
#
#- Removes every object inside $(OBJDIR) and the directory itself.					-#
clean:
	@rm -rf $(OBJDIR)
	@echo "$(COLOUR_BLUE)[i] $(CNAME) - Object cleaning complete.\n$(COLOUR_END)"
#
#- Removes the final files made with this makefile, executing clean as well.		-#
fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOUR_RED)[X] $(CNAME) - Files removed.\n$(COLOUR_END)"
#
#- Restarts the Makefile. Erases everything to default, and executes again.			-#
re: fclean all