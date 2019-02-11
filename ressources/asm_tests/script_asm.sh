# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    script_asm.sh                                    .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: ybarraul <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/01/29 13:43:35 by ybarraul     #+#   ##    ##    #+#        #
#    Updated: 2019/02/01 17:44:32 by sifouche    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #


MY_ASM="./asm/asm"
REAL_ASM="./ressources/asm"

S=".s"
C=".cor"

CHAMPS_PATH_KO="./ressources/asm_tests/champs_error/"
CHAMPS_PATH_OK_ERROR="./ressources/asm_tests/champ_good/error/"
CHAMPS_PATH_OK_SUCCES="./ressources/asm_tests/champ_good/Succes/"

RED="\\033[1;31m"
GREEN="\\033[1;32m"
CYAN="\033[1;34m"

clear ; touch a b c;
echo $CYAN "Testing Champion in file -> $CHAMPS_PATH_KO\n"

for i in $CHAMPS_PATH_KO*
do
	rm a b c 
	touch a b c 
	$MY_ASM $i > c
	mv ${i%??}$C a 2>/dev/null
	$REAL_ASM $i > c
	mv ${i%??}$C b 2>/dev/null
	if cmp a b 2>/dev/null;
	then echo $GREEN "$i - [OK]"; \
else echo $RED "$i - [KO]" ; cmp a b;\
	fi
done

echo $CYAN "\n\nTesting Champion in file -> $CHAMPS_PATH_OK_ERROR\n"

for i in $CHAMPS_PATH_OK_ERROR*
do
	rm a b c 
	touch a b c 
	$MY_ASM $i > c
	mv ${i%??}$C a 2>/dev/null
	$REAL_ASM $i > c 
	mv ${i%??}$C b 2>/dev/null
	if cmp a b 2>/dev/null;
	then echo $GREEN "$i - [OK]"; \
		else echo $RED "$i - [KO]" ; cmp a b;\
	fi
done

echo $CYAN "\n\nTesting Champion in file -> $CHAMPS_PATH_OK_SUCCES\n"

for i in $CHAMPS_PATH_OK_SUCCES*
do
	rm a b c
	touch a b c
	$MY_ASM $i > c
	mv ${i%??}$C a 2>/dev/null
	$REAL_ASM $i > c
	mv ${i%??}$C b 2>/dev/null
	if cmp a b 2>/dev/null;
	then echo $GREEN "$i - [OK]"; \
		else echo $RED "$i - [KO]" ; cmp a b;\
	fi
done
rm a b c;
