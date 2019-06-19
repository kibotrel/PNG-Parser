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

#include "libft.h"
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

static void	verbose(t_control file)
{
	ft_putstr("\nChunk name       : ");
	ft_putstr(file.chunk.name);
	ft_putstr("\n\nChunk size       : ");
	ft_putnbr(file.chunk.size);
	ft_putstr("\nPNG size         : ");
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
}

int			header(t_control *file)
{
	if (file->chunk.size != 13)
		return (ERR_IHDR);
	if (file->info.chunk)
		return (ERR_FORMAT);
	fill_infos(&file->info, (unsigned char*)file->save, file->info.position);
	if (file->verbose)
		verbose(*file);
	if (!file->info.width || !file->info.height)
		return (ERR_SIZE);
	if (file->info.depth > 16 || !is_power_two(file->info.depth))
		return (ERR_DEPTH);
	if (file->info.color > 6 || file->info.color == 1 || file->info.color == 5)
		return (ERR_COLOR);
	if (!check_presets(file->info.depth, file->info.color))
		return (ERR_PRESET);
	if (file->info.depth != 8
		|| (file->info.color != 2 && file->info.color != 6)
		|| file->info.compression || file->info.filter || file->info.interlace)
		return (ERR_HANDLED);
	return (SUCCESS);
}
