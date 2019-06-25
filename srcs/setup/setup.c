/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:09:02 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/25 16:54:03 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "macros.h"
#include "png.h"

void	get_chunkname(char *chunk, unsigned char *save, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		chunk[i] = save[i];
	chunk[i] = '\0';
}

void	set_array(t_control *file, t_png *image)
{
	image->pixels = file->pixels;
	image->width = file->info.width;
	image->height = file->info.height;
	image->size = image->width * image->height;
}

void	setup(t_control *file, t_png *image, int flag)
{
	ft_bzero(&file->info, sizeof(t_infos));
	ft_bzero(file, sizeof(t_control));
	ft_bzero(image, sizeof(t_png));
	file->info.pos = 8;
	file->verbose = (flag == VERBOSE ? ON : OFF);
	file->debug = (flag == DEBUG ? ON : OFF);
}
