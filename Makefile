# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/22 19:07:47 by sscheini          #+#    #+#              #
#    Updated: 2026/03/22 20:27:57 by sscheini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	================================ Main Configuration ================================	#

#	Executable names
NAME = miniRT
NAME_BONUS = miniRT_bonus

#	Source files
MAIN_SRC =	$(SOURCE_DIR)/main.c								\
			$(SOURCE_DIR)/libs/rtapp/rtapp.c					\
			$(SOURCE_DIR)/libs/rterr/rterr_log.c				\
			$(SOURCE_DIR)/libs/rtapp/rtapp_init/parser.c		\
			$(SOURCE_DIR)/libs/rtapp/rtapp_init/init_log.c		\
			$(SOURCE_DIR)/libs/rtapp/rtapp_init/init_objlst.c	\

BONUS_SRC = $(SOURCE_DIR)/main_bonus.c

#	================================ Library Configuration =============================	#

#	Libraries to build (in build order)
LIBS = libs/libft #librtapp #minilibx #librterr #librtmlx #librtmth

#	Library linking order: most dependent first, base libraries last
LINK_LIBS = -l:libft.a #librtapp #librterr #librtmth #librtmlx #minilibx #libft

#	Library linking order for bonus build
LINK_LIBS_BONUS = #librtapp_bonus #librterr #librtmth #librtmlx #minilibx #libft

# ================================ Directory Structure =============================== #

# Source, Object, and Dependency directories
SOURCE_DIR = src
OBJECT_DIR = obj
DEPEND_DIR = dep

# Include paths for headers
INCLUDE_DIRS = -I include/ -I include/rtapp/ -I include/elements/ -I src/libs/libft/include/ -I src/libs/minilibx/

# Library paths for linking
LIBRARY_PATHS = $(addprefix -L $(SOURCE_DIR)/, $(LIBS))

# ================================ Compiler Settings ================================= #

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g

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

.PHONY: all bonus clean fclean re

# Default: build main program
all: $(NAME)
	@echo "$(COLOR_GREEN)[✓] $(NAME) - Build complete!$(COLOR_RESET)\n"

# Build bonus program
bonus: $(NAME_BONUS)
	@echo "$(COLOR_GREEN)[✓] $(NAME) - Bonus build complete!$(COLOR_RESET)\n"

msg:
	@echo "$(COLOR_BLUE)[i] $(NAME) - Main Compilation:"

msg_bonus:
	@echo "$(COLOR_BLUE)[i] $(NAME) - Main Bonus Compilation:"

# ================================ Directory Creation ================================ #

$(OBJECT_DIR) $(DEPEND_DIR):
	@mkdir -p $@/libs/elements
	@mkdir -p $@/libs/rtapp
	@mkdir -p $@/libs/rterr
	@mkdir -p $@/libs/rtmlx
	@mkdir -p $@/libs/rtmth
	@mkdir -p $@/libs/rtapp/rtapp_init

# ================================ Library Building ================================== #

# Build each library in its subdirectory
$(LIBS):
	@$(MAKE) -s -C $(SOURCE_DIR)/$@

# Build each library in its subdirectory
libs_bonus: $(LIBS)
	@$(MAKE) bonus -s -C $(SOURCE_DIR)/mshft

# ================================ Object Compilation ================================ #

# Compile source files to object files
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c | $(DEPEND_DIR) $(OBJECT_DIR)
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPFLAGS) -c $< -o $@ -MF $(DEPEND_DIR)/$(@F:.o=.d)
	@printf "\r\t$(COLOR_GREEN)[OK] Compiled $<$(COLOR_RESET)"

# Include dependency files for header tracking
-include $(DEPENDENCIES)

# ================================ Linking =========================================== #

# Link main executable
# Order: compiler, object files, library paths, libraries, output
$(NAME): $(LIBS) msg $(MAIN_OBJ)
	@$(CC) $(CFLAGS) $(MAIN_OBJ) $(LDFLAGS) $(LINK_LIBS) -o $@
	@printf "\r\t$(COLOR_CYAN)[OK] Main compiled successfully.\n$(COLOR_RESET)"
	@echo "$(COLOR_BLUE)[✓] $(NAME) - Linked successfully$(COLOR_RESET)\n"

# Link bonus executable
$(NAME_BONUS): libs_bonus msg_bonus $(BONUS_OBJ)
	@$(CC) $(CFLAGS) -D BONUS=1 $(BONUS_OBJ) $(LDFLAGS) $(LINK_LIBS_BONUS) -o $@
	@printf "\r\t$(COLOR_CYAN)[OK] Main compiled successfully.\n$(COLOR_RESET)"
	@echo "$(COLOR_BLUE)[✓] $(NAME) - Linked successfully$(COLOR_RESET)\n"

# ================================ Cleanup Rules ===================================== #

# Remove object and dependency files
clean:
	@$(foreach lib, $(LIBS), $(MAKE) -s -C $(SOURCE_DIR)/$(lib) clean;)
	@rm -rf $(OBJECT_DIR) $(DEPEND_DIR)
	@echo "$(COLOR_BLUE)[i] Cleaned build artifacts$(COLOR_RESET)\n"

# Remove everything including executables
fclean: clean
	@$(foreach lib, $(LIBS), $(MAKE) -s -C $(SOURCE_DIR)/$(lib) fclean;)
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "$(COLOR_RED)[x] Full clean complete$(COLOR_RESET)\n"

# Rebuild from scratch
re: fclean all