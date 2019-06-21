/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:16:22 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/21 01:27:36 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "macros.h"
#include "png.h"

static void	get_chunk_infos(t_infos *info, unsigned char *buffer, int offset)
{
	info->chunk++;
	info->width = big_endian4(buffer + offset - 8);
	info->height = big_endian4(buffer + offset - 4);
	info->depth = buffer[offset++];
	info->color = buffer[offset++];
	info->compression = buffer[offset++];
	info->filter = buffer[offset++];
	info->interlace = buffer[offset++];
	if (info->color == 2 || info->color == 6)
		info->channels = (info->color == 2 ? 3 : 4);
	else if (!info->color || info->color == 4)
		info->channels = (!info->color ? 1 : 2);
	if (info->channels)
	{
		info->bpp = (info->depth / 8) * info->channels;
		info->scanline = 1 + info->bpp * info->width;
		info->raw = info->scanline * info->height;
	}
}

static void	verbose(t_control file)
{
	print_chunk_basics(file.chunk.name, file.chunk.size);
	ft_putstr("\nImage dimensions : ");
	ft_putnbr(file.info.width);
	ft_putchar('x');
	ft_putnbr(file.info.height);
	ft_putstr("\nBit depth        : ");
	ft_putnbr(file.info.depth);
	ft_putstr("\nColor type       : ");
	ft_putnbr(file.info.color);
	ft_putstr("\nCompression type : ");
	ft_putnbr(file.info.compression);
	ft_putstr("\nFilter type      : ");
	ft_putnbr(file.info.filter);
	ft_putstr("\nInterlace type   : ");
	ft_putnbr(file.info.interlace);
	ft_putstr("\nPixel channels   : ");
	ft_putnbr(file.info.channels);
	ft_putstr("\nBytes per pixel  : ");
	ft_putnbr(file.info.bpp);
	ft_putstr("\nScanline size    : ");
	ft_putnbr(file.info.scanline);
	ft_putstr("\nRaw size         : ");
	ft_putnbr(file.info.raw);
	ft_putstr("\n");
}

int			header(t_control *file)
{
	if (file->chunk.size != 13)
		return (ERR_IHDR);
	if (file->info.chunk)
		return (ERR_FORMAT);
	get_chunk_infos(&file->info, file->save, file->info.pos + 16);
	if (file->verbose)
		verbose(*file);
	if (!file->info.width || !file->info.height)
		return (ERR_SIZE);
	if (file->info.depth > 16 || !is_power_two(file->info.depth))
		return (ERR_DEPTH);
	if (file->info.color > 6 || file->info.color == 1 || file->info.color == 5)
		return (ERR_COLOR);
	if (check_presets(file->info.depth, file->info.color))
		return (ERR_PRESET);
	if (file->info.depth != 8
		|| (file->info.color != 2 && file->info.color != 6)
		|| file->info.compression || file->info.filter || file->info.interlace)
		return (ERR_HANDLED);
	return (SUCCESS);
}
