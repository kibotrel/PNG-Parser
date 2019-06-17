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

static void	fill_infos(t_infos *info, unsigned char *buffer, int offset)
{
	int	i;

	i = offset + 16;
	info->chunk++;
	info->width = big_endian4(buffer + i - 8);
	info->height = big_endian4(buffer + i - 4);
	info->depth = buffer[i++];
	info->color = buffer[i++];
	info->compression = buffer[i++];
	info->filter = buffer[i++];
	info->interlace = buffer[i++];
}

static int	check_presets(unsigned char depth, unsigned char clr)
{
	return (((clr == 3 && depth == 16)
			|| ((clr == 2 || clr == 4 || clr == 6) && depth < 8)) ? 0 : 1);
}

void		header(t_control *file)
{
	if (file->chunk.size != 13 || file->info.chunk)
		clean(file->save, ERR_HEADER, 4);
	fill_infos(&file->info, (unsigned char*)file->save, file->info.position);
	if (!file->info.width || !file->info.height)
		clean(file->save, ERR_SIZE, 5);
	if (file->info.depth > 16 || !is_power_two(file->info.depth))
		clean(file->save, ERR_DEPTH, 7);
	if (file->info.color > 6 || file->info.color == 1 || file->info.color == 5)
		clean(file->save, ERR_COLOR, 8);
	if (!check_presets(file->info.depth, file->info.color))
		clean(file->save, ERR_PRESET, 9);
	if (file->verbose)
	{
		printf("\nChunk name         : %s\n", file->chunk.name);
		printf("\nChunk size         : %d\n", file->chunk.size);
		printf("PNG size           : %dx%dp\n", file->info.width, file->info.height);
		printf("Bit depth          : %d\n", file->info.depth);
		printf("Color type         : %d\n", file->info.color);
		printf("Compression method : %d\n", file->info.compression);
		printf("Filter method      : %d\n", file->info.filter);
		printf("Interlace method   : %d\n", file->info.interlace);
	}
}
