/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/26 15:43:06 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/01/30 18:30:45 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/uio.h>

typedef struct	s_gnl
{
	int					fd;
	char				*leftover;
	struct s_gnl		*next;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif
