/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:03:23 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/25 17:10:44 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PNG_H
# define PNG_H

typedef struct		s_chunk
{
	int				size;
	char			name[5];
	unsigned char	length[4];
}					t_chunk;

typedef struct		s_infos
{
	int				pos;
	int				width;
	int				height;
	int				scanline;
	unsigned int	raw;
	unsigned int	chunk;
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
	unsigned int	*pixels;
	unsigned char	*raw;
	unsigned char	*save;
	unsigned char	*stream;
}					t_control;

typedef struct		s_png
{
	int				width;
	int				height;
	unsigned int	size;
	unsigned int	*pixels;
}					t_png;

/*
**	setup/setup.c
*/

void				set_array(t_control *file, t_png *image);
void				setup(t_control *file, t_png *image, int flag);
void				get_chunkname(char *chunk, unsigned char *save, int size);

/*
**	chunks/header.c
*/

int					header(t_control *file);

/*
**	chunks/end.c
*/

int					end(t_control *file);

/*
**	chunks/signature.c
*/

int					check_signature(unsigned char *buffer);

/*
**	chunks/time.c
*/

int					time(t_control *file);

/*
**	chunks/image.c
*/

int					image(t_control *file);

/*
**	core/png_to_array.c
*/

int					png_to_array(char *png, t_png *image, int flag);

/*
**	core/selector.c
*/

int					selector(t_control *file);
void				unfilter(t_control *file, int y, int filter);

/*
**	utils/maths.c
*/

int					is_power_two(int nb);
int					big_endian2(unsigned char *nb);
int					big_endian4(unsigned char *nb);
unsigned int		create_pixel(unsigned char *raw, int bpp, int pos);
unsigned char		predict(unsigned char a, unsigned char b, unsigned char c);

/*
**	utils/display.c
*/

void				print_chunks(t_control file);
void				flag_mode(int verbose, int debug);
void				print_state(t_control file, int code);
void				print_memory(t_control file, int state);
void				print_chunk_basics(char *name, int size);

/*
**	utils/errors.c
*/

int					output(t_control file, int code);
int					check_presets(unsigned char depth, unsigned char color);
void				is_valid_read(int size, int *out);

/*
**	utils/filters.c
*/

void				up(unsigned char *raw, int h, int y);
void				sub(unsigned char *raw, int bpp, int h, int y);
void				paeth(unsigned char *raw, int bpp, int h, int y);
void				average(unsigned char *raw, int bpp, int h, int y);

#endif
