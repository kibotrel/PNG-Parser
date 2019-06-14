/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:09:02 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/14 16:10:51 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "png.h"

void		fill_chunkname(char *chunk, char *buffer, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		chunk[i] = buffer[i];
	chunk[i] = '\0';
}

static void	fill_handler(t_process *handler)
{
	handler[0].type = "IHDR";
	handler[0].process = header;
	handler[1].type = NULL;
	handler[1].process = NULL;
}

void		setup(t_control *file, t_process *handler)
{
	fill_handler(handler);
	file->info.position = 8;
	file->info.chunk = 0;
}
