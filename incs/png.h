/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:03:23 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/25 14:58:16 by kibotrel         ###   ########.fr       */
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

int					is_power_two(int nb);
int					end(t_control *file);
int					time(t_control *file);
int					image(t_control *file);
int					header(t_control *file);
int					selector(t_control *file);
int					big_endian4(unsigned char *nb);
int					big_endian2(unsigned char *nb);
int					output(t_control file, int code);
int					check_signature(unsigned char *buffer);
int					png_to_array(char *png, t_png *image, int flag);
int					check_presets(unsigned char depth, unsigned char color);
void				print_chunks(t_control file);
void				setup(t_control *file, t_png *image, int flag);
void				flag_mode(int verbose, int debug);
void				is_valid_read(int size, int *out);
void				up(unsigned char *raw, int h, int y);
void				print_state(t_control file, int code);
void				print_memory(t_control file, int state);
void				set_array(t_control *file, t_png *image);
void				print_chunk_basics(char *name, int size);
void				unfilter(t_control *file, int y, int filter);
void				sub(unsigned char *raw, int bpp, int h, int y);
void				paeth(unsigned char *raw, int bpp, int h, int y);
void				average(unsigned char *raw, int bpp, int h, int y);
void				get_chunkname(char *chunk, unsigned char *save, int size);
unsigned char		predict(unsigned char a, unsigned char b, unsigned char c);

#endif
