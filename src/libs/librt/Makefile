# --------------------------------- Makefile Main ---------------------------------- #

SRC		=	$(SRCDIR)$(APPDIR)rtapp_init/init_file.c					\
			$(SRCDIR)$(APPDIR)rtapp_init/init_objlst.c					\
			$(SRCDIR)$(APPDIR)rtapp_init/init_obj_utils.c				\
			$(SRCDIR)$(APPDIR)rtapp_init/init_elm_utils.c				\
			$(SRCDIR)$(APPDIR)rtapp_init/parser/parse_line.c			\
			$(SRCDIR)$(APPDIR)rtapp_init/parser/parse_plane.c			\
			$(SRCDIR)$(APPDIR)rtapp_init/parser/parse_sphere.c			\
			$(SRCDIR)$(APPDIR)rtapp_init/parser/parse_cylinder.c		\
			$(SRCDIR)$(APPDIR)rtapp_init/parser/parse_ambient_light.c	\
			$(SRCDIR)$(APPDIR)rtapp_init/parser/parse_camera.c			\
			$(SRCDIR)$(APPDIR)rtapp_init/parser/parse_light.c			\
			$(SRCDIR)$(APPDIR)rtapp_init/parser/parse_utils.c			\
			$(SRCDIR)$(APPDIR)rtapp.c									\
			$(SRCDIR)$(ELMDIR)plane.c									\
			$(SRCDIR)$(ELMDIR)sphere.c									\
			$(SRCDIR)$(ELMDIR)cylinder.c								\
			$(SRCDIR)$(ELMDIR)ambient_light.c							\
			$(SRCDIR)$(ELMDIR)camera.c									\
			$(SRCDIR)$(ELMDIR)light.c									\
			$(SRCDIR)$(MTHDIR)matrix/mat4.c								\
			$(SRCDIR)$(MTHDIR)matrix/mat4_inverse.c						\
			$(SRCDIR)$(MTHDIR)matrix/mat4_transforms.c					\
			$(SRCDIR)$(MTHDIR)equations/quadratic.c						\
			$(SRCDIR)$(MTHDIR)raytracing/ray.c							\
			$(SRCDIR)$(MTHDIR)raytracing/vector_mat4.c					\
			$(SRCDIR)$(MTHDIR)vector/vector.c							\
			$(SRCDIR)$(MTHDIR)vector/vector_vector.c					\
			$(SRCDIR)$(MTHDIR)vector/vector_scalar.c					\
			$(SRCDIR)$(ERRDIR)rtlog.c									\
			$(SRCDIR)$(ERRDIR)rtfree.c									\
			$(SRCDIR)$(APPDIR)rtapp_init/init_log.c						\
			#init_log.c wont be here, only in bonus

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
CFLAGS	=	-g -Wall -Werror -Wextra -I include/ -I include/rtapp -I include/rtelm -I ../libft/include

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
	@echo "$(COLOUR_GREEN)$(CNAME) - Object compilation:\n"
	@mkdir -p $@$(APPDIR)rtapp_init/
	@mkdir -p $@$(APPDIR)rtapp_init/parser
	@mkdir -p $@$(APPDIR)rtapp_render/
	@mkdir -p $@$(APPDIR)rtapp_run/
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
	@echo "$(COLOUR_CIAN)\t-$@ created."
#
#- Complies the $(NAME) library.													-#
$(NAME): $(OBJDIR) $(OBJ)
	@ar rcs $(NAME) $(OBJ) $(LIBDIR)
	@echo "$(COLOUR_GREEN)\$(CNAME) - Library $@ linked.$(COLOUR_END)"
#
#- Removes every object inside $(OBJDIR) and the directory itself.					-#
clean:
	@rm -rf $(OBJDIR)
	@echo "$(COLOUR_RED)$(CNAME) - Object cleaning complete.\n$(COLOUR_END)"
#
#- Removes the final files made with this makefile, executing clean as well.		-#
fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOUR_RED)$(CNAME) - Files removed.\n$(COLOUR_END)"
#
#- Restarts the Makefile. Erases everything to default, and executes again.			-#
re: fclean all