#include "libft.h"
#include "macros.h"
#include "png.h"

static void	verbose(t_control file)
{
	chunk_infos(file.chunk.name, file.chunk.size);
}

int			end(t_control *file)
{
	if (file->chunk.size != 0)
		return (ERR_IEND);
	if (!file->info.chunk || file->info.iend || !file->info.idat)
		return (ERR_FORMAT);
	file->info.iend = 1;
	if (file->verbose)
		verbose(*file);
	return (SUCCESS);
}
