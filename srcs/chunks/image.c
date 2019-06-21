/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 04:53:26 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/21 06:07:09 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "zlib.h"
#include "libft.h"
#include "macros.h"
#include "png.h"

static int	get_raw_chunk(t_control *file)
{
	z_stream		z;

	if (!(file->raw = (unsigned char*)malloc(file->info.raw + 1)))
		return (ERROR);
	z.zalloc = Z_NULL;
	z.zfree = Z_NULL;
	z.opaque = Z_NULL;
	z.avail_in = file->chunk.size;
	z.next_in = (Bytef*)file->stream;
	z.avail_out = file->info.raw;
	z.next_out = (Bytef*)file->raw;
	inflateInit2_(&z, 15, ZLIB_VERSION, sizeof(z));
	inflate(&z, Z_NO_FLUSH);
	inflateEnd(&z);
	return (SUCCESS);
}

static int	get_pixel_values(t_control *file, int w, int h)
{
	int				line;
	int				filter;
	unsigned int	pos;

	pos = 0;
	line = 0;
	if (!(file->pixels = (unsigned int*)malloc(sizeof(unsigned int) * w * h)))
		return (ERROR);
	ft_bzero(file->pixels, sizeof(unsigned int) * w * h);
	while (pos < file->info.raw)
	{
		if ((filter = file->raw[file->info.scanline * line]) > 4)
			return (ERROR);
		unfilter(file, line, filter);
		line++;
		pos += file->info.scanline;
	}
	return (SUCCESS);
}

int			image(t_control *file)
{
	if (file->chunk.size == 0)
		return (ERR_IDAT);
	if (!file->info.chunk || file->info.iend)
		return (ERR_FORMAT);
	if (file->info.idat)
		return (ERR_HANDLED);
	file->info.idat = 1;
	ft_putchar('\n');
	file->verbose ? print_chunk_basics(file->chunk.name, file->chunk.size) : 0;
	if (!(file->stream = (unsigned char*)ft_strnew(IDAT_BUFFER)))
		return (ERR_IMAGE);
	ft_memcpy(file->stream, file->save + file->info.pos + 8, file->chunk.size);
	if (get_raw_chunk(file))
		return (ERR_IMAGE);
	if (get_pixel_values(file, file->info.width, file->info.height))
		return (ERR_IMAGE);
	if (file->verbose)
	{
		print_memory(*file);
		ft_putchar('\n');
	}
	free(file->stream);
	free(file->raw);
	return (SUCCESS);
}
