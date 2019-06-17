#include <stdio.h>
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

void		time(t_control *file)
{
	if (file->chunk.size != 7 || !file->info.chunk)
		clean(file->save, ERR_TIME, 12);
	if (file->info.iend || file->info.time)
		clean(file->save, ERR_FORMAT, 11);
	fill_infos(&file->info, (unsigned char*)file->save, file->info.position);
	file->info.time = 1;
	if (file->info.hours > 23 || file->info.mins > 59 || file->info.secs > 60
		|| !file->info.day || file->info.day > 31
		|| !file->info.month || file->info.month > 12)
		clean(file->save, ERR_DATE, 13);
	if (file->verbose)
	{
		printf("\nChunk name         : %s\n", file->chunk.name);
		printf("\nChunk size         : %d\n", file->chunk.size);
		printf("Year               : %d\n", file->info.year);
		printf("Month              : %d\n", file->info.month);
		printf("Day                : %d\n", file->info.day);
		printf("Hours              : %d\n", file->info.hours);
		printf("Minutes            : %d\n", file->info.mins);
		printf("Seconds            : %d\n", file->info.secs);
	}
}
