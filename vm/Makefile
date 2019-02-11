#  ************************************************************************** # 
#                                                           LE - /            # 
#                                                               /             # 
#    Makefile                                         .::    .:/ .      .::   # 
#                                                  +:+:+   +:    +:  +:+:+    # 
#    By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     # 
#                                                  #+#   #+    #+    #+#      # 
#    Created: 2019/01/17 17:20:38 by asiaux       #+#   ##    ##    #+#       # 
#    Updated: 2019/01/28 16:42:18 by sifouche    ###    #+. /#+    ###.fr      #
#                                                          /                  # 
#                                                         /                   # 
#  ************************************************************************** # 


.PHONY = $(POINTA) all clean fclean re

# **************************************************************************** #
#																			   #
#									DIRECTORIES		    					   #
#																			   #
# **************************************************************************** #

SRCDIR = ./src/
OBJDIR = ./obj/
HEADERDIR = ./includes/
LIBFTDIR = ../ressources/libft/

# **************************************************************************** #
#																			   #
#		           			    	FILES		    						   #
#																			   #
# **************************************************************************** #

NAME = corewar
CC = gcc
CFLAGS = -Werror -Wall -Wextra
POINTA = $(addprefix $(LIBFTDIR), libft.a)
HEADERS = $(addprefix $(HEADERDIR), vm.h)

FILESCOR =	err_exit \
			vm_game \
			vm_init \
			vm_main \
			vm_op1 \
			vm_op2 \
            vm_op3 \
            vm_op4 \
            vm_op_check \
            vm_op_exec \
            vm_op_read_params \
            vm_parse \
            vm_parse_utils \
            vm_proc_utils \
            vm_utils \
            vm_verbose

SRCCOR = $(addprefix $(SRCDIR), $(addsuffix .c, $(FILESCOR)))
OBJCOR = $(addprefix $(OBJDIR), $(addsuffix .o, $(FILESCOR)))

SRCS = $(SRCCOR)
OBJS = $(OBJCOR)

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
