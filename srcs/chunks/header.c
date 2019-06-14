/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:16:22 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/14 16:16:23 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "macros.h"
#include "png.h"

static void	fill_infos(t_infos *info, char *buffer)
{
	info->chunk++;
	info->width = big_endian(buffer);
	info->height = big_endian(buffer + 4);
	info->depth = (unsigned char)buffer[8];
	info->color = (unsigned char)buffer[9];
	info->compression = (unsigned char)buffer[10];
	info->filter = (unsigned char)buffer[11];
	info->interlace = (unsigned char)buffer[12];
}

static int	check_presets(unsigned char depth, unsigned char clr)
{
	return (((clr == 3 && depth == 16)
			|| ((clr == 2 || clr == 4 || clr == 6) && depth < 8)) ? 0 : 1);
}

void		header(char *buffer, t_control *file)
{
	if (file->chunk.size != 13 || file->info.chunk)
		clean(buffer, ERR_HEADER, 4);
	fill_infos(&file->info, buffer);
	if (!file->info.width || !file->info.height)
		clean(buffer, ERR_SIZE, 5);
	if (file->info.depth > 16 || !is_power_two(file->info.depth))
		clean(buffer, ERR_DEPTH, 7);
	if (file->info.color > 6 || file->info.color == 1 || file->info.color == 5)
		clean(buffer, ERR_COLOR, 8);
	if (!check_presets(file->info.depth, file->info.color))
		clean(buffer, ERR_PRESET, 9);
	printf("\nChunk name         : %s\nPNG size           : %dx%dp\n", file->chunk.name, file->info.width, file->info.height);
	printf("Bit depth          : %d\nColor type         : %d\n", file->info.depth, file->info.color);
	printf("Compression method : %d\nFilter method      : %d\n", file->info.compression, file->info.filter);
	printf("Interlace method   : %d\n\n", file->info.interlace);
}
