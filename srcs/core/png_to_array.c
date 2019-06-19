/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_to_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:16:17 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/14 16:25:10 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "macros.h"
#include "png.h"

static void	png_structure(t_control file, char *save)
{
	ft_putendl("\n--- Debug mode ---\n\nChunks :\n");
	while (file.info.position < file.size)
	{
		ft_memcpy(file.chunk.length, save + file.info.position, 4);
		file.chunk.size = big_endian4(file.chunk.length);
		fill_chunkname(file.chunk.name, save + file.info.position + 4, 4);
		ft_putendl(file.chunk.name);
		file.info.position += file.chunk.size + 12;
	}
}

static int	read_png(t_control *file, char *save)
{
	int				i;
	int 			out;
	t_process		handler[NB_CHUNKS + 1] = {{NULL, NULL}};

	file->verbose ? ft_putendl("\n--- Verbose mode ---") : 0;
	setup(file, handler);
	file->debug ? png_structure(*file, file->save) : 0;
	out = check_signature(save);
	while (!out && file->info.position < file->size)
	{
		i = -1;
		ft_memcpy(file->chunk.length, save + file->info.position, 4);
		file->chunk.size = big_endian4(file->chunk.length);
		fill_chunkname(file->chunk.name, save + file->info.position + 4, 4);
		while (handler[++i].type)
			if (!ft_strcmp(handler[i].type, file->chunk.name))
			{
				out = handler[i].process(file);
				break;
			}
		file->info.position += file->chunk.size + 12;
	}
	return (out);
}

static void	debug(t_control file, int code)
{
	if (code && !file.debug)
		ft_putstr("\n\n");
	else
		ft_putchar('\n');
	ft_putstr("PNG Parser exit with code ");
	ft_putnbr(code);
	ft_putstr(" on chunk ");
	ft_putstr(file.chunk.name);
	ft_putstr(".\n");
}

int			png_to_array(char *png, int flag)
{
	int				out;
	FILE			*f;
	t_control		file;

	out = 0;
	if (!(file.save = (char*)malloc(MAX_SIZE)))
		out = ERR_MALLOC;
	if (!out && !(f = fopen(png, "r")))
		out = ERR_OPEN;
	if (!out)
	{
		file.size = fread(file.save, sizeof(char), MAX_SIZE, f);
		file.verbose = (flag == VERBOSE ? ON : OFF);
		file.debug = (flag == DEBUG ? ON : OFF);
		if (file.size <= MAX_SIZE && feof(f) && !ferror(f) && !fclose(f))
			out = read_png(&file, file.save);
		else
			out = ERR_FILE;
	}
	out != ERR_MALLOC ? free(file.save) : 0;
	if (file.debug)
		debug(file, out);
	return (process_state(file, out));
}
