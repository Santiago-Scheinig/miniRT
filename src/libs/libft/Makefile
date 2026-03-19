# --------------------------------- Makefile Main ---------------------------------- #

SRC		=	$(SRCDIR)ft_argjoin.c					\
			$(SRCDIR)ft_atoi.c						\
			$(SRCDIR)ft_atol.c						\
			$(SRCDIR)ft_atoi_base.c					\
			$(SRCDIR)ft_bzero.c						\
			$(SRCDIR)ft_calloc.c					\
			$(SRCDIR)ft_iq_split.c					\
			$(SRCDIR)ft_iq_strchr.c					\
			$(SRCDIR)ft_itoa.c						\
			$(SRCDIR)ft_isalnum.c					\
			$(SRCDIR)ft_isascii.c					\
			$(SRCDIR)ft_isalpha.c					\
			$(SRCDIR)ft_isdigit.c					\
			$(SRCDIR)ft_isprint.c					\
			$(SRCDIR)ft_lstnew_bonus.c				\
			$(SRCDIR)ft_lstmap_bonus.c				\
			$(SRCDIR)ft_lstiter_bonus.c				\
			$(SRCDIR)ft_lstlast_bonus.c				\
			$(SRCDIR)ft_lstsize_bonus.c				\
			$(SRCDIR)ft_lstclear_bonus.c			\
			$(SRCDIR)ft_lstdelone_bonus.c			\
			$(SRCDIR)ft_lstadd_back_bonus.c			\
			$(SRCDIR)ft_lstadd_front_bonus.c		\
			$(SRCDIR)ft_memchr.c					\
			$(SRCDIR)ft_memcmp.c					\
			$(SRCDIR)ft_memcpy.c					\
			$(SRCDIR)ft_memset.c					\
			$(SRCDIR)ft_memmove.c					\
			$(SRCDIR)ft_printfd.c					\
			$(SRCDIR)ft_printf_utils.c				\
			$(SRCDIR)ft_printf_bonus.c				\
			$(SRCDIR)ft_printf_flags_bonus.c		\
			$(SRCDIR)ft_printf_utils_bonus.c		\
			$(SRCDIR)ft_putnbr_fd.c					\
			$(SRCDIR)ft_putstr_fd.c					\
			$(SRCDIR)ft_putchar_fd.c				\
			$(SRCDIR)ft_putendl_fd.c				\
			$(SRCDIR)ft_read_file.c					\
			$(SRCDIR)ft_split.c						\
			$(SRCDIR)ft_split_free.c				\
			$(SRCDIR)ft_strchr.c					\
			$(SRCDIR)ft_strdup.c					\
			$(SRCDIR)ft_strlen.c					\
			$(SRCDIR)ft_strjoin.c					\
			$(SRCDIR)ft_strlcat.c					\
			$(SRCDIR)ft_strlcpy.c					\
			$(SRCDIR)ft_strmapi.c					\
			$(SRCDIR)ft_strncmp.c					\
			$(SRCDIR)ft_strnstr.c					\
			$(SRCDIR)ft_strrchr.c					\
			$(SRCDIR)ft_strtrim.c					\
			$(SRCDIR)ft_striteri.c					\
			$(SRCDIR)ft_substr.c					\
			$(SRCDIR)ft_tolower.c					\
			$(SRCDIR)ft_toupper.c					\
			$(SRCDIR)ft_utoa_base.c					\
			$(SRCDIR)get_next_line.c				\
			$(SRCDIR)get_next_line_utils.c			\
#
SRCDIR	=	src/
OBJDIR	=	obj/
INCDIR	=	-I include/

NAME	=	libft.a

CC		=	cc
GCC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror $(INCDIR) -g

# --------------------------- Makefile Object Compilation -------------------------- #

OBJ		=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

# ------------------------------- Makefile Cosmetics ------------------------------- #

CNAME			=	Libft
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
	@echo "$(COLOUR_GREEN)Libft - Object compilation:\n"
	@mkdir -p $@
#
#- Compiles each %(generic).c source into its respective %(generic).o				-#
$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(COLOUR_CIAN)\t-$@ created."
#
#- Complies the $(NAME) library.													-#
$(NAME): $(OBJDIR) $(OBJ)
	@ar rcs $(NAME) $(OBJ) $(LIBDIR)
	@echo "$(COLOUR_GREEN)\n$(CNAME) - Library $@ linked.$(COLOUR_END)"
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