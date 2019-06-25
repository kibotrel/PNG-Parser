/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 04:53:14 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/25 17:18:53 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "png.h"

void	sub(unsigned char *raw, int bpp, int h, int y)
{
	int				x;
	unsigned char	left;
	unsigned char	current;

	x = 0;
	while (++x < h)
	{
		current = raw[x + y * h];
		if (x >= bpp + 1)
		{
			left = raw[x + y * h - bpp];
			raw[x + y * h] = (current + left) % 256;
		}
	}
}

void	up(unsigned char *raw, int h, int y)
{
	int				x;
	unsigned char	up;
	unsigned char	current;

	x = 0;
	while (++x < h)
	{
		current = raw[x + y * h];
		if (y)
		{
			up = raw[x + (y - 1) * h];
			raw[x + y * h] = (current + up) % 256;
		}
	}
}

void	average(unsigned char *raw, int bpp, int h, int y)
{
	int				x;
	unsigned char	up;
	unsigned char	left;
	unsigned char	current;

	x = 0;
	while (++x < h)
	{
		current = raw[x + y * h];
		up = raw[x + (y - 1) * h];
		left = raw[x + y * h - bpp];
		if (!y && x >= bpp + 1)
			raw[x + y * h] = (int)(current + floor((left / 2))) % 256;
		else if (y && x < bpp + 1)
			raw[x + y * h] = (int)(current + floor((up / 2))) % 256;
		else if (y && x >= bpp + 1)
			raw[x + y * h] = (int)(current + floor(((left + up) / 2))) % 256;
	}
}

void	paeth(unsigned char *raw, int bpp, int h, int y)
{
	int				x;
	unsigned char	up;
	unsigned char	left;
	unsigned char	corner;
	unsigned char	current;

	x = 0;
	while (++x < h)
	{
		current = raw[x + y * h];
		up = raw[x + (y - 1) * h];
		left = raw[x + y * h - bpp];
		corner = raw[x + (y - 1) * h - bpp];
		if (!y && x >= bpp + 1)
			raw[x + y * h] = (current + predict(left, 0, 0)) % 256;
		else if (y && x < bpp + 1)
			raw[x + y * h] = (current + predict(0, up, 0)) % 256;
		else if (y && x >= bpp + 1)
			raw[x + y * h] = (current + predict(left, up, corner)) % 256;
	}
}
