/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 04:53:42 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/25 16:44:45 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macros.h"
#include "png.h"

int			end(t_control *file)
{
	if (file->chunk.size != 0)
		return (ERR_IEND);
	if (!file->info.chunk || file->info.iend || !file->info.idat)
		return (ERR_FORMAT);
	file->info.iend = 1;
	if (file->verbose)
		print_chunk_basics(file->chunk.name, file->chunk.size);
	return (SUCCESS);
}
