#  ************************************************************************** # 
#                                                           LE - /            # 
#                                                               /             # 
#    Makefile                                         .::    .:/ .      .::   # 
#                                                  +:+:+   +:    +:  +:+:+    # 
#    By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     # 
#                                                  #+#   #+    #+    #+#      # 
#    Created: 2019/01/17 17:20:38 by asiaux       #+#   ##    ##    #+#       # 
#    Updated: 2019/02/15 12:48:14 by sifouche    ###    #+. /#+    ###.fr      #
#                                                          /                  # 
#                                                         /                   # 
#  ************************************************************************** # 

.PHONY = $(POINTA) all clean fclean re

# **************************************************************************** #
#																			   #
#									DIRECTORIES		    					   #
#																			   #
# **************************************************************************** #

SRCDIR = ./
OBJDIR = ./obj/
HEADERDIR = ./
LIBFTDIR = ../ressources/libft/

# **************************************************************************** #
#																			   #
#		           			    	FILES		    						   #
#																			   #
# **************************************************************************** #

NAME = asm
CC = gcc
CFLAGS = -Werror -Wall -Wextra
POINTA = $(addprefix $(LIBFTDIR), libft.a)
HEADERS = $(addprefix $(HEADERDIR), asm.h)

FILESASM =	fill_labels_val \
			find_label \
			find_op \
			get_champinfo \
			get_line \
			get_line_utils \
			get_param \
			is_valid_item \
			lst_labels \
			lst_operations \
			main \
			parse_arg \
			parse_file \
			print_cor \
			print_header

SRCASM = $(addprefix $(SRCDIR), $(addsuffix .c, $(FILESASM)))
OBJASM = $(addprefix $(OBJDIR), $(addsuffix .o, $(FILESASM)))

SRCS = $(SRCASM)
OBJS = $(OBJASM)

# **************************************************************************** #
#																			   #
#									COMMANDS								   #
#																			   #
# **************************************************************************** #

all : $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(POINTA)
	@printf "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(POINTA)
	@printf "\033[32m[OK]\033[0m\n"

$(OBJDIR):
	@mkdir -p $@

$(POINTA):
	@printf "Compiling libft..."
	@make -C $(LIBFTDIR) || true
	@printf "\033[32m[OK]\033[0m\n"

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADERS)
	@printf "%b" "Compiling $< in $@..."
	@$(CC) $(CFLAGS) -o $@ -c $< -I $(HEADERS)
	@printf "\033[32m[OK]\033[0m\n"

clean:
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFTDIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)

re: fclean all
