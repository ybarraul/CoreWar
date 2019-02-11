/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 16:55:26 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 16:54:54 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "../../ressources/libft/includes/libft.h"

# define PROG_NAME_LENGTH       (128)
# define COMMENT_LENGTH         (2048)
# define COREWAR_EXEC_MAGIC     0xea83f3
# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define REG_NUMBER				16
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

extern char			g_opname[16][10];

typedef struct		s_proc
{
	int				id;
	int				player_id;
	int				reg[16];
	int				pc;
	int				pc_origin;
	int				alive;
	int				last_live;
	int				carry;
	int				wait;
	int				next_op;
	struct s_proc	*next;
	struct s_proc	*last;
}					t_proc;

typedef struct		s_player
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
	int				p_id;
	int				last_live;
}					t_player;

typedef struct		s_vm
{
	unsigned char	*arena;
	char			flags;
	int				nb_players;
	t_player		players[4];
	int				proc_nb;
	t_proc			*proc;
	int				nb_live;
	int				cur_cycle;
	int				tot_cycle;
	int				max_cycle;
	int				dump_cycle;
	int				last_check;
	int				winner;
	int				op_timer[16];
}					t_vm;

typedef struct		s_ocp
{
	int t_un;
	int s_un;
	int v_un;
	int t_de;
	int s_de;
	int v_de;
	int t_tr;
	int s_tr;
	int v_tr;
}					t_ocp;

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

/*
** FUNCTIONS
*/

void				new_proc(t_vm *vm, t_proc **start, int player_id, int pc);
void				del_proc(t_vm *vm, t_proc **start, t_proc *proc);
void				cpy_proc(t_proc *src, t_proc *dst);
void				dump_arena(t_vm *vm);
void				vm_init(t_vm *vm);
void				vm_game(t_vm *vm);
void				vm_free(t_vm *vm);
int					main(int argc, char **argv);
void				vm_parse(t_vm *vm, char **argv);
int					read_special_p(t_vm *vm, t_proc *p, int op);
int					read_p(t_vm *vm, t_proc *p, int size);
int					read_bytes(t_vm *vm, int size, int i);
void				write_on_arena(t_vm *vm, int val, int adr);
void				exec_op(t_vm *vm, t_proc *p, t_ocp *o, int op);
int					read_params(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				read_ocp(t_ocp *o, unsigned char ocp, int no_ocp);
int					check_p(int param, int r, int d, int i);
int					verif_valid_ocp(t_ocp *o, int op);
int					get_params_size(t_ocp *o, int op);
int					is_valid_op(t_vm *vm, t_proc *p);
void				op_live(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				op_ld(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				op_st(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				op_add(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				op_sub(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				op_and(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				op_or(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				op_xor(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				op_zjmp(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				op_ldi(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				op_sti(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				op_fork(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				op_lld(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				op_lldi(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				op_lfork(t_vm *vm, t_proc *p, t_ocp *o, int op);
void				op_aff(t_vm *vm, t_proc *p, t_ocp *o);
void				verbose_mvt(t_vm *vm, t_proc *p, int mvt);
void				solo_exit(char *msg, t_vm *vm);
void				string_exit(char *msg, char *param, t_vm *vm);
int					check_ifstrdigit(char *to_check);
int					check_dot_cor(char *str);
unsigned int		swap_bytes(unsigned int byte);
void				vm_decrement_cycles(t_vm *vm);
int					nb(char **av);

#endif
