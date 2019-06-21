/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:03:23 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/21 08:27:40 by kibotrel         ###   ########.fr       */
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

int					is_power_two(int nb);
int					end(t_control *file);
int					time(t_control *file);
int					image(t_control *file);
int					header(t_control *file);
int					selector(t_control *file);
int					big_endian4(unsigned char *nb);
int					big_endian2(unsigned char *nb);
int					output(t_control file, int code);
int					png_to_array(char *png, int flag);
int					check_signature(unsigned char *buffer);
int					check_presets(unsigned char depth, unsigned char color);
void				up(t_control *file, int y);
void				sub(t_control *file, int y);
void				print_chunks(t_control file);
void				print_memory(t_control file);
void				paeth(t_control *file, int y);
void				average(t_control *file, int y);
void				setup(t_control *file, int flag);
void				flag_mode(int verbose, int debug);
void				is_valid_read(int size, int *out);
void				print_state(t_control file, int code);
void				print_chunk_basics(char *name, int size);
void				unfilter(t_control *file, int y, int filter);
void				get_chunkname(char *chunk, unsigned char *save, int size);
unsigned char		predict(unsigned char a, unsigned char b, unsigned char c);

#endif
