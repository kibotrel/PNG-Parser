#include "libft.h"
#include "macros.h"
#include "png.h"

static void	fill_infos(t_infos *info, unsigned char *buffer, int offset)
{
	int	i;

	i = offset + 10;
	info->chunk++;
	info->year = big_endian2(buffer + i - 2);
	info->month = buffer[i++];
	info->day = buffer[i++];
	info->hours = buffer[i++];
	info->mins = buffer[i++];
	info->secs = buffer[i++];
}

static void	verbose(t_control file)
{
	ft_putstr("\n\nChunk name       : ");
	ft_putstr(file.chunk.name);
	ft_putstr("\n\nChunk size       : ");
	ft_putnbr(file.chunk.size);
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
	fill_infos(&file->info, (unsigned char*)file->save, file->info.position);
	file->info.time = 1;
	if (file->verbose)
		verbose(*file);
	if (file->info.hours > 23 || file->info.mins > 59 || file->info.secs > 60
		|| !file->info.day || file->info.day > 31
		|| !file->info.month || file->info.month > 12)
		return (ERR_DATE);
	return (SUCCESS);
}
