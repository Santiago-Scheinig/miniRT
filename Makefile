# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/22 19:07:47 by sscheini          #+#    #+#              #
#    Updated: 2026/04/11 20:33:02 by sscheini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	================================ Main Configuration ================================	#

#	Executable names
NAME = miniRT
NAME_BONUS = miniRT_bonus

#	Source files
MAIN_SRC =	$(SOURCE_DIR)/main.c										\
			$(SOURCE_DIR)/rtapp/rtapp_init/parser/parse_ambient_light.c	\
			$(SOURCE_DIR)/rtapp/rtapp_init/parser/parse_camera.c		\
			$(SOURCE_DIR)/rtapp/rtapp_init/parser/parse_cylinder.c		\
			$(SOURCE_DIR)/rtapp/rtapp_init/parser/parse_light.c			\
			$(SOURCE_DIR)/rtapp/rtapp_init/parser/parse_line.c			\
			$(SOURCE_DIR)/rtapp/rtapp_init/parser/parse_plane.c			\
			$(SOURCE_DIR)/rtapp/rtapp_init/parser/parse_sphere.c		\
			$(SOURCE_DIR)/rtapp/rtapp_init/parser/parse_utils.c			\
			$(SOURCE_DIR)/rtapp/rtapp_init/init_elm_utils.c				\
			$(SOURCE_DIR)/rtapp/rtapp_init/init_file.c						\
			$(SOURCE_DIR)/rtapp/rtapp_init/init_obj_utils.c					\
			$(SOURCE_DIR)/rtapp/rtapp_init/init_objlst.c						\
			$(SOURCE_DIR)/rtapp/rtapp_render/tile_queue.c				\
			$(SOURCE_DIR)/rtapp/rtapp.c									\
			$(SOURCE_DIR)/rtapp/rtlog.c									\

BONUS_SRC = $(SOURCE_DIR)/main_bonus.c

#	================================ Library Configuration =============================	#

#	Libraries to build (in build order)
LIBS = libs/libft libs/librt #minilibx

#	Library linking order: most dependent first, base libraries last
LINK_LIBS = -l:librt.a -l:libft.a -lm #minilibx

#	Library linking order for bonus build
LINK_LIBS_BONUS = #librtapp_bonus #librterr #librtmth #librtmlx #minilibx #libft

# ================================ Directory Structure =============================== #

# Source, Object, and Dependency directories
SOURCE_DIR = src
OBJECT_DIR = obj
DEPEND_DIR = dep

# Include paths for headers
INCLUDE_DIRS = -I include -I libs/libft/include -I libs/librt/include -I libs/librt/include/rtelm -I src/libs/minilibx/

# Library paths for linking
LIBRARY_PATHS = $(addprefix -L, $(LIBS))

# ================================ Compiler Settings ================================= #

DEV ?= 0

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g -D DEV=$(DEV)

# Dependency generation flags
DEPFLAGS = -MMD -MP

# Preprocessor flags (includes)
CPPFLAGS = $(INCLUDE_DIRS)

# Linker flags (library paths)
LDFLAGS = $(LIBRARY_PATHS)

# ================================ Object Files ====================================== #

# Main program objects
MAIN_OBJ = $(MAIN_SRC:$(SOURCE_DIR)/%.c=$(OBJECT_DIR)/%.o)

# Bonus program objects
BONUS_OBJ = $(BONUS_SRC:$(SOURCE_DIR)/%.c=$(OBJECT_DIR)/%.o)

# Dependency files
ALL_SOURCES = $(MAIN_SRC) $(BONUS_SRC)
DEPENDENCIES = $(ALL_SOURCES:$(SOURCE_DIR)/%.c=$(DEPEND_DIR)/%.d)

# ================================ Colors for Output ================================= #

COLOR_RED = \033[0;31m
COLOR_GREEN = \033[0;32m
COLOR_BLUE = \033[0;34m
COLOR_CYAN = \033[0;35m
COLOR_RESET = \033[0m

# ================================ Build Rules ======================================= #

.PHONY: all dev bonus clean fclean re $(LIBS)

# Default: build main program
all: $(NAME)
	@echo "$(COLOR_GREEN)[✓] $(NAME) - Build complete!$(COLOR_RESET)\n"

# Developer mode
dev:
	@$(MAKE) -s re DEV=1
	@echo "$(COLOR_GREEN)[✓] $(NAME) - Dev build complete!$(COLOR_RESET)\n"

# Build bonus program
bonus: $(NAME_BONUS)
	@echo "$(COLOR_GREEN)[✓] $(NAME) - Bonus build complete!$(COLOR_RESET)\n"

msg:
	@echo "$(COLOR_BLUE)[i] $(NAME) - Object compilation:"

start_msg:
	@echo "$(COLOR_GREEN)[⚙] $(NAME) - Building:\n"

# ================================ Directory Creation ================================ #

$(OBJECT_DIR) $(DEPEND_DIR):
	@mkdir -p $@
	@mkdir -p $@/rtapp
	@mkdir -p $@/rtapp/rtapp_init
	@mkdir -p $@/rtapp/rtapp_init/parser
	@mkdir -p $@/rtapp/rtapp_render
	@mkdir -p $@/rtapp/rtapp_run

# ================================ Library Building ================================== #

# Build each library in its subdirectory
$(LIBS):
	@$(MAKE) -s -C $@

# Build each library in its subdirectory
libs_bonus: $(LIBS)
	@$(MAKE) bonus -s -C $(SOURCE_DIR)/mshft

# ================================ Object Compilation ================================ #

# Compile source files to object files
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c | $(DEPEND_DIR) $(OBJECT_DIR)
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPFLAGS) -c $< -o $@ -MF $(DEPEND_DIR)/$(@F:.o=.d)
	@printf "\r\033[2K\t$(COLOR_GREEN)[⚙] $< created.$(COLOR_RESET)"

# Include dependency files for header tracking
-include $(DEPENDENCIES)

# ================================ Linking =========================================== #

# Link main executable
# Order: compiler, object files, library paths, libraries, output
$(NAME): start_msg $(LIBS) msg $(MAIN_OBJ)
	@$(CC) $(CFLAGS) $(MAIN_OBJ) $(LDFLAGS) $(LINK_LIBS) -o $@
	@printf "\r\t$(COLOR_CYAN)[OK] Program compiled successfully.\n\n$(COLOR_RESET)"

# Link bonus executable
$(NAME_BONUS): libs_bonus msg_bonus $(BONUS_OBJ)
	@$(CC) $(CFLAGS) -D BONUS=1 $(BONUS_OBJ) $(LDFLAGS) $(LINK_LIBS_BONUS) -o $@
	@printf "\r\t$(COLOR_CYAN)[OK] Main compiled successfully.\n$(COLOR_RESET)"

# ================================ Cleanup Rules ===================================== #

# Remove object and dependency files
clean:
	@$(foreach lib, $(LIBS), $(MAKE) -s -C $(lib) clean;)
	@rm -rf $(OBJECT_DIR) $(DEPEND_DIR)
	@echo "$(COLOR_BLUE)[i] $(NAME) - Cleaned build artifacts$(COLOR_RESET)\n"

# Remove everything including executables
fclean:
	@$(foreach lib, $(LIBS), $(MAKE) -s -C $(lib) fclean;)
	@rm -rf $(OBJECT_DIR) $(DEPEND_DIR)
	@echo "$(COLOR_BLUE)[i] $(NAME) - Object cleaning complete.\n$(COLOUR_END)"
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "$(COLOR_RED)[X] $(NAME) - Full clean complete$(COLOR_RESET)\n"

# Rebuild from scratch
re: fclean all