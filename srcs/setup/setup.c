/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:09:02 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/20 23:02:39 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

void	setup(t_control *file, int flag)
{
	ft_bzero(&file->info, sizeof(t_infos));
	ft_bzero(file, sizeof(t_control));
	file->info.pos = 8;
	file->verbose = (flag == VERBOSE ? ON : OFF);
	file->debug = (flag == DEBUG ? ON : OFF);
}
