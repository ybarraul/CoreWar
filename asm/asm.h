/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 18:07:31 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 12:54:14 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "../ressources/libft/includes/libft.h"

# define SEMI_COLON_OK			1
# define SEPARATOR_CHAR			','
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"
# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		s_param
{
	int				val;
	int				size;
	int				type;
	char			*label;
}					t_param;

typedef struct		s_ope
{
	int				op;
	char			opc;
	int				size;
	t_param			p_un;
	t_param			p_de;
	t_param			p_tr;
	struct s_ope	*next;
}					t_ope;

typedef struct		s_lab
{
	int				pos;
	char			*name;
	struct s_lab	*next;
}					t_lab;

typedef struct		s_line
{
	char			*line;
	char			*lfree;
	int				size;
	int				nb;
}					t_line;

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_op
{
	char			s_op[6];
	int				op_arg;
	int				opc[3];
	int				opnum;
	int				timer;
	char			descr[1024];
	int				has_opc;
	int				dir_size_two;
}					t_op;

typedef struct		s_asm
{
	t_header		h;
	t_line			ln;
	t_lab			*lst_lab;
	t_ope			*lst_ope;
}					t_asm;

extern t_op			g_op_tab[16];

void				verif_valid_arg(int argc, char **argv);

void				read_file(t_asm *a, char *file);
int					readline(t_asm *a, int fd);
void				realloc_line(t_asm *a, int i);
int					sanitize_line(t_asm *a, int res, int i);
void				get_champ_info(t_asm *a, int fd);
int					check_label(t_asm *a, int pos);
int					check_op(t_asm *a);
void				get_param(t_asm *a, t_param *p, int op);
int					is_valid_label(char *line, int i_stop);
int					is_valid_p(char *line);

void				fill_label_val(t_asm *a);

void				print_header(t_asm *a, int fd_dest);
void				print_cor(t_asm *a, int fd_dest);

void				lst_lab_push(t_asm *a, char *name, int pos);
void				lst_lab_del_all(t_asm *a);
void				lst_ope_push(t_asm *a, t_ope *ope);
void				lst_ope_del_all(t_asm *a);

void				free_all(t_asm *a);

#endif
