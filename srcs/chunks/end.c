#include "stdio.h"
#include "macros.h"
#include "png.h"

void	end(t_control *file)
{
	if (file->chunk.size != 0 || !file->info.chunk)
		clean(file->save, ERR_END, 10);
	if (file->info.iend)// || !file->info.idat)
		clean(file->save, ERR_FORMAT, 11);
	file->info.iend = 1;
	if (file->verbose)
	{
		printf("\nChunk name         : %s\n", file->chunk.name);
		printf("\nChunk size         : %d\n\n", file->chunk.size);
	}
}
