/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:03:23 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/14 16:20:44 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PNG_H
# define PNG_H

typedef struct		s_chunk
{
	int				size;
	unsigned char	name[5];
	unsigned char	length[4];
}					t_chunk;

typedef struct		s_infos
{
	int				pos;
	int				width;
	int				height;
	unsigned int	raw;
	unsigned int	chunk;
	unsigned int	scanline;
	unsigned char	bpp;
	unsigned char	day;
	unsigned char	mins;
	unsigned char	secs;
	unsigned char	time;
	unsigned char	idat;
	unsigned char	iend;
	unsigned char	hours;
	unsigned char	month;
	unsigned char	color;
	unsigned char	depth;
	unsigned char	filter;
	unsigned char	channels;
	unsigned char	interlace;
	unsigned char	compression;
	unsigned short	year;
}					t_infos;

typedef struct		s_control
{
	int				size;
	int				debug;
	int				verbose;
	t_infos			info;
	t_chunk			chunk;
	unsigned char	*raw;
	unsigned char	*save;
	unsigned char	*stream;
}					t_control;

typedef int			(*handler)(t_control *file);

typedef struct		s_process
{
	char			*type;
	handler			process;
}					t_process;

int					is_power_two(int nb);
int					end(t_control *file);
int					time(t_control *file);
int					image(t_control *file);
int					header(t_control *file);
int					process_state(t_control file, int code);
int					check_signature(unsigned char *buffer);
int					big_endian4(unsigned char *nb);
int					big_endian2(unsigned char *nb);
int					png_to_array(char *png, int flag);
void				chunk_infos(unsigned char *name, int size);
void				setup(t_control *file, t_process *handler);
void				fill_chunkname(unsigned char *chunk, unsigned char *save,
									int size);

#endif
