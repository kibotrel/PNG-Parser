#include "stdio.h"
#include "macros.h"
#include "png.h"

void	end(char *buffer, t_control *file)
{
	if (file->chunk.size != 0 || !file->info.chunk)
		clean(buffer, ERR_END, 10);
	if (!file->info.idat)
		clean(buffer, ERR_FORMAT, 11);
	if (file->verbose)
	{
		printf("\nChunk name         : %s\n", file->chunk.name);
		printf("\nChunk size         : %d\n", file->chunk.size);
	}
}
