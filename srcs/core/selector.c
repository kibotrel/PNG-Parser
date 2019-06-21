/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 20:10:23 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/21 07:37:46 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "macros.h"
#include "png.h"

int		selector(t_control *file)
{
	if (!ft_strcmp(file->chunk.name, "IHDR"))
		return(header(file));
	else if (!ft_strcmp(file->chunk.name, "tIME"))
		return(time(file));
	else if (!ft_strcmp(file->chunk.name, "IDAT"))
		return(image(file));
	else if (!ft_strcmp(file->chunk.name, "IEND"))
		return(end(file));
	return (SUCCESS);
}

void	unfilter(t_control *file, int y, int filter)
{
	if (filter == 1)
		sub(file, y);
	if (filter == 2)
		up(file, y);
	if (filter == 3)
		average(file, y);
	// if (filter == 4)
	// 	paeth(file, y);
}
