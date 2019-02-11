# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    test.sh                                          .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/01/28 15:39:13 by sifouche     #+#   ##    ##    #+#        #
#    Updated: 2019/02/05 16:58:25 by sifouche    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

LOCAL_VM="./vm/corewar"
REAL_VM="./ressources/corewar"
VERBOSE="-v 30"
DUMP="-d 10000"

CHAMPS_PATH="./ressources/vm_tests/examples/"

RED="\\033[1;31m"
GREEN="\\033[1;32m"
CYAN="\033[1;34m"

echo $CYAN "Testing vms $LOCAL_VM and $REAL_VM"
echo $CYAN " - Verbose value : $VERBOSE"
echo $CYAN " - Dump value : $DUMP\n"

touch a b c ; rm a b c
for i in $CHAMPS_PATH*
do
	for j in $CHAMPS_PATH*
	do
		$LOCAL_VM $VERBOSE $DUMP $i $j > a
		$REAL_VM $VERBOSE $DUMP $i $j > b
		if diff a b > c;
		then echo $GREEN "$i vs $j - [OK]"; \
		else echo $RED "$i vs $j - [KO]" && cat c > d;\
		fi
	done
done
rm a b c;
