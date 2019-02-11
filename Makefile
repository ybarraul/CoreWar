# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: ybarraul <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/01/29 14:31:57 by ybarraul     #+#   ##    ##    #+#        #
#    Updated: 2019/01/29 18:10:10 by sifouche    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY = $(POINTA) all clean fclean re script script_asm script_vm comp cor

NAME = asm && vm

# **************************************************************************** #
#																			   #
#									DIRECTORIES		    					   #
#																			   #
# **************************************************************************** #

ASMDIR = ./asm/
VMDIR = ./vm/
SCRIPT_ASM = ./ressources/asm_tests/
SCRIPT_VM = ./ressources/vm_tests/

# **************************************************************************** #
#																			   #
#									COMMANDS								   #
#																			   #
# **************************************************************************** #

all : $(NAME)

$(NAME):
	@printf "\033[34m[ASM]\033[0m\n"
	@make -C $(ASMDIR)
	@printf "\033[34m[VM]\033[0m\n"
	@make -C $(VMDIR)
	@printf "\033[32m[OK]\033[0m\n"

comp:
	make -C $(ASMDIR)

cor:
	make -C $(VMDIR)

clean:
	@printf "\033[34m[Clean ASM]\033[0m\n"
	@make clean -C $(ASMDIR)
	@printf "\033[34m[Clean VM]\033[0m\n"
	@make clean -C $(VMDIR)
	@printf "\033[32m[OK]\033[0m\n"

fclean: clean
	@printf "\033[34m[Fclean ASM]\033[0m\n"
	@make fclean -C $(ASMDIR)
	@printf "\033[34m[Fclean VM]\033[0m\n"
	@make fclean -C $(VMDIR)
	@printf "\033[32m[OK]\033[0m\n"

script: script_asm script_vm

script_asm:
	@printf "\033[31m[Script ASM]\033[0m\n"
	@$(SCRIPT_ASM)script_asm.sh

script_vm:
	@printf "\033[31m[Script VM]\033[0m\n"
	@$(SCRIPT_VM)script_vm.sh

re: fclean all
