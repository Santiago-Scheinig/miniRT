# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/22 19:07:47 by sscheini          #+#    #+#              #
#    Updated: 2026/06/09 18:11:56 by sscheini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================ Main Configuration ============================ #

NAME        = miniRT
NAME_BONUS  = miniRT_bonus

MAIN_SRC	=	$(SOURCE_DIR)/main.c									\
				$(SOURCE_DIR)/rtapp/rtapp.c								\
				$(SOURCE_DIR)/rtapp/debug/rtlog.c						\
				$(SOURCE_DIR)/rtapp/init/init_file.c					\
				$(SOURCE_DIR)/rtapp/init/init_elements.c				\
				$(SOURCE_DIR)/rtapp/init/parser/parse_line.c			\
				$(SOURCE_DIR)/rtapp/init/parser/parse_lights.c			\
				$(SOURCE_DIR)/rtapp/init/parser/parse_objects.c			\
				$(SOURCE_DIR)/rtapp/init/parser/parse_utils.c			\
				$(SOURCE_DIR)/rtapp/render/tile_queue.c					\
				$(SOURCE_DIR)/rtapp/render/get_color_at_hit.c			\
				$(SOURCE_DIR)/rtapp/render/get_hit_from_ray.c			\

BONUS_SRC	=	$(filter-out											\
				$(SOURCE_DIR)/rtapp/rtapp.c								\
				$(SOURCE_DIR)/rtapp/init/init_elements.c				\
				$(SOURCE_DIR)/rtapp/init/parser/parse_lights.c			\
				$(SOURCE_DIR)/rtapp/init/parser/parse_objects.c			\
				$(SOURCE_DIR)/rtapp/render/get_color_at_hit.c,			\
				$(MAIN_SRC))											\
				$(SOURCE_DIR)/rtapp/rtapp_bonus.c						\
				$(SOURCE_DIR)/rtapp/init/init_elements_bonus.c			\
				$(SOURCE_DIR)/rtapp/init/init_log_bonus.c				\
				$(SOURCE_DIR)/rtapp/init/parser/parse_lights_bonus.c	\
				$(SOURCE_DIR)/rtapp/init/parser/parse_objects_bonus.c	\
				$(SOURCE_DIR)/rtapp/init/parser/parse_utils_bonus.c		\
				$(SOURCE_DIR)/rtapp/render/get_color_at_hit_bonus.c		\
				$(SOURCE_DIR)/rtapp/render/get_lighting_bonus.c			\
				$(SOURCE_DIR)/rtapp/render/get_material_bonus.c			\
				$(SOURCE_DIR)/rtapp/render/normal_map_bonus.c			\
				$(SOURCE_DIR)/rtapp/render/rtapp_render_bonus.c\
				

# ================================ Library Configuration ========================= #

LIBS        = libs/librt

LINK_LIBS   = -l:librt.a -l:libft.a -l:libmlx_Linux.a -lm -lX11 -lXext

LINK_LIBS_BONUS   = -l:librt_bonus.a -l:libft.a -l:libmlx_Linux.a -lm -lX11 -lXext -lpthread

# ================================ Directory Structure =========================== #

SOURCE_DIR  = src
OBJECT_DIR  = obj
DEPEND_DIR  = dep

INCLUDE_DIRS    = -I include						\
				  -I libs/librt/include				\
				  -I libs/librt/libs/libft/include	\
				  -I libs/librt/libs/minilibx		\

LIBRARY_PATHS   = -L libs/librt					\
				  -L libs/librt/libs/libft		\
				  -L libs/librt/libs/minilibx	\

# ================================ Compiler Settings ============================ #

DEV ?= 0
W_WIDTH ?= 1920
W_HEIGHT ?= 1080

CFLAGS      = -Wall -Wextra -Werror -g -D DEV=$(DEV) -D W_HEIGHT=$(W_HEIGHT) -D W_WIDTH=$(W_WIDTH)
DEPFLAGS    = -MMD -MP
CPPFLAGS    = $(INCLUDE_DIRS)
LDFLAGS     = $(LIBRARY_PATHS)

# ================================ Object Files ================================== #

MAIN_OBJ    	= 	$(MAIN_SRC:$(SOURCE_DIR)/%.c=$(OBJECT_DIR)/%.o)
BSRC			=	$(BONUS_SRC)
BONUS_OBJ		= 	$(BSRC:$(SOURCE_DIR)/%.c=$(OBJECT_DIR)/bonus/%.o)
DEPENDENCIES	=	$(MAIN_SRC:$(SOURCE_DIR)/%.c=$(DEPEND_DIR)/%.d) \
               		$(BONUS_SRC:$(SOURCE_DIR)/%.c=$(DEPEND_DIR)/%.d)

# ================================ Colors ======================================== #

COLOR_RED   = \033[0;31m
COLOR_GREEN = \033[0;32m
COLOR_BLUE  = \033[0;34m
COLOR_CYAN  = \033[0;35m
COLOR_RESET = \033[0m

# ================================ Build Rules =================================== #

.PHONY: all msg dev bonus clean fclean re $(LIBS)

all: $(NAME)

dev:
	@$(MAKE) -s re DEV=1

bonus: $(NAME_BONUS)

# ================================ Directory Creation ============================ #

msg:
	@echo "$(COLOR_BLUE)[i] $(NAME) - Object compilation:"

$(OBJECT_DIR) $(DEPEND_DIR): msg
	@mkdir -p $@/rtapp/debug
	@mkdir -p $@/rtapp/init/parser
	@mkdir -p $@/rtapp/render
	@mkdir -p $@/rtapp/run

# ================================ Library Building ============================== #

$(LIBS):
	@$(MAKE) -s -C $@ W_HEIGHT=$(W_HEIGHT) W_WIDTH=$(W_WIDTH)

libs_bonus:
	@$(MAKE) bonus -s -C $(LIBS) W_HEIGHT=$(W_HEIGHT) W_WIDTH=$(W_WIDTH)

# ================================ Object Compilation ============================ #

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c | $(DEPEND_DIR) $(OBJECT_DIR)
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPFLAGS) -c $< -o $@ -MF $(DEPEND_DIR)/$(@F:.o=.d)
	@printf "\r\033[2K\t$(COLOR_GREEN)[⚙] $< created.$(COLOR_RESET)"

$(OBJECT_DIR)/bonus/%.o: $(SOURCE_DIR)/%.c | $(DEPEND_DIR) $(OBJECT_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -D BONUS=1 $(DEPFLAGS) -c $< -o $@ -MF $(DEPEND_DIR)/$(@F:.o=.d)
	@printf "\r\033[2K\t$(COLOR_GREEN)[⚙] $< created.$(COLOR_RESET)"

-include $(DEPENDENCIES)

# ================================ Linking ======================================= #

$(NAME): $(LIBS) $(MAIN_OBJ)
	@$(CC) $(CFLAGS) $(MAIN_OBJ) $(LDFLAGS) $(LINK_LIBS) -o $@
	@printf "\r\033[2K\t$(COLOR_CYAN)[OK] Program compiled successfully.\n\n$(COLOR_RESET)"
	@printf "\033[2K$(COLOR_GREEN)[✓] $(NAME) - Build complete.\n\n$(COLOR_RESET)"

$(NAME_BONUS): libs_bonus $(BONUS_OBJ)
	@$(CC) $(CFLAGS) -D BONUS=1 $(BONUS_OBJ) $(LDFLAGS) $(LINK_LIBS_BONUS) -o $@
	@printf "\r\033[2K\t$(COLOR_CYAN)[OK] Program compiled successfully.\n\n$(COLOR_RESET)"
	@printf "\033[2K$(COLOR_GREEN)[✓] $(NAME_BONUS) - Build complete.\n\n$(COLOR_RESET)"
# ================================ Cleanup ======================================= #

clean:
	@$(foreach lib, $(LIBS), $(MAKE) -s -C $(lib) clean;)
	@if [ -d $(OBJECT_DIR) ]; then \
		rm -rf $(OBJECT_DIR) $(DEPEND_DIR); \
		printf "$(COLOR_BLUE)[i] $(NAME) - Object cleaning complete. \n$(COLOUR_END)\n"; \
	fi
	@echo "$(COLOR_GREEN)[✓] $(NAME) - Cleaned build artifacts.$(COLOR_RESET)\n"

fclean: clean
	@$(foreach lib, $(LIBS), $(MAKE) -s -C $(lib) fclean;)
	@if [ -f $(NAME) ] || [ -f $(NAME_BONUS) ]; then \
		rm -f $(NAME) $(NAME_BONUS); \
		echo "$(COLOR_RED)[X] $(NAME) - Files removed.\n$(COLOUR_END)"; \
	fi
	@if [ -f "vlog.txt" ]; then	\
		rm -rf "vlog.txt";	\
	fi
	@echo "$(COLOR_GREEN)[✓] $(NAME) - Full clean complete.$(COLOR_RESET)\n"

re: fclean all