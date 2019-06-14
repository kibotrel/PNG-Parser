/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:03:23 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/14 16:04:28 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PNG_H
# define PNG_H

typedef struct		s_chunk
{
	int				size;
	char			name[5];
	char			length[4];
}					t_chunk;

typedef struct		s_infos
{
	int				chunk;
	int				width;
	int				height;
	int				position;
	unsigned char	color;
	unsigned char	depth;
	unsigned char	filter;
	unsigned char	interlace;
	unsigned char	compression;
}					t_infos;

typedef struct		s_control
{
	int				size;
	t_chunk			chunk;
	t_infos			info;
}					t_control;

typedef void		(*handler)(char *buffer, t_control *file);

typedef struct		s_process
{
	char			*type;
	handler			process;
}					t_process;

int					is_power_two(int nb);
int					big_endian(char *length);
void				png_to_bmp(char *png);
void				header(char *buffer, t_control *file);
void				clean(char *buffer, char *error, int code);
void				setup(t_control *file, t_process *handler);
void				fill_chunkname(char *chunk, char *buffer, int size);

#endif
