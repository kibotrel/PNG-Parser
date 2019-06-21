/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 04:53:30 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/21 04:53:31 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "macros.h"
#include "png.h"

static void	fill_infos(t_infos *info, unsigned char *buffer, int offset)
{
	info->chunk++;
	info->year = big_endian2(buffer + offset - 2);
	info->month = buffer[offset++];
	info->day = buffer[offset++];
	info->hours = buffer[offset++];
	info->mins = buffer[offset++];
	info->secs = buffer[offset++];
}

static void	verbose(t_control file)
{
	ft_putchar('\n');
	print_chunk_basics(file.chunk.name, file.chunk.size);
	ft_putstr("\nYear             : ");
	ft_putnbr(file.info.year);
	ft_putstr("\nMonth            : ");
	ft_putnbr(file.info.month);
	ft_putstr("\nDay              : ");
	ft_putnbr(file.info.day);
	ft_putstr("\nHours            : ");
	ft_putnbr(file.info.hours);
	ft_putstr("\nMinutes          : ");
	ft_putnbr(file.info.mins);
	ft_putstr("\nSeconds          : ");
	ft_putnbr(file.info.secs);
}

int			time(t_control *file)
{
	if (file->chunk.size != 7 || !file->info.chunk)
		return (ERR_TIME);
	if (file->info.iend || file->info.time)
		return (ERR_FORMAT);
	fill_infos(&file->info, (unsigned char*)file->save, file->info.pos + 10);
	file->info.time = 1;
	file->verbose ? verbose(*file) : 0;
	if (file->info.hours > 23 || file->info.mins > 59 || file->info.secs > 60)
		return (ERR_DATE);
	if (!file->info.day || file->info.day > 31 || !file->info.month)
		return (ERR_DATE);
	if (file->info.month > 12)
		return (ERR_DATE);
	return (SUCCESS);
}
