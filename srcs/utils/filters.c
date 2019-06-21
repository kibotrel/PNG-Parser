/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 04:53:14 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/21 08:34:07 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "png.h"

#include <stdio.h>

void	sub(t_control *file, int y)
{
	int	x;
	int	bpp;
	int	line;

	x = 0;
	bpp = file->info.bpp;
	line = file->info.scanline;
	while(++x < line)
	{
		if (x < bpp + 1)
			file->raw[x + y * line] = file->raw[x + y * line];
		else
			file->raw[x + y * line] = (file->raw[x + y * line] + file->raw[x + y * line - bpp]) % 256;
	}
}

void	up(t_control *file, int y)
{
	int	x;
	int	bpp;
	int	line;

	x = 0;
	bpp = file->info.bpp;
	line = file->info.scanline;
	while(++x < file->info.scanline)
	{
		if (!y)
			file->raw[x + y * line] = 0;
		else
			file->raw[x + y * line] = (file->raw[x + y * line]
				+ file->raw[(x + (y - 1) * line) - bpp]) % 256;
	}
}

void	average(t_control *file, int y)
{
	int	x;
	int	bpp;
	int	line;

	x = -1;
	(void)y;
	bpp = file->info.bpp;
	line = file->info.scanline;
	while(++x < file->info.scanline)
		line = file->info.scanline;
}

void	paeth(t_control *file, int y)
{
	int	x;
	int	bpp;
	int	line;

	x = 0;
	bpp = file->info.bpp;
	line = file->info.scanline;
	while(++x < file->info.scanline)
	{
		if (!y)
		{
			if (x >= bpp + 1)
				file->raw[x + y * line] = (file->raw[x + y * line]
					+ predict(file->raw[x + y * line - bpp], 0, 0)) % 256;
		}
		else
		{
			if (x < bpp + 1)
			{
				file->raw[x + y * line] = (file->raw[x + y * line - bpp]
					+ predict(0, file->raw[x + (y - 1) * line], 0)) % 256;
			}
			else
			{
				file->raw[x + y * line] = (file->raw[x + y * line]
					+ predict(file->raw[x + y * line - bpp],
						file->raw[x + (y - 1) * line],
						file->raw[x + (y - 1) * line - bpp])) % 256;
			}
		}
	}
}
