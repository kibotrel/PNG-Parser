#include "libft.h"
#include "macros.h"
#include "png.h"

static void	verbose(t_control file)
{
	ft_putstr("\n\nChunk name       : ");
	ft_putstr(file.chunk.name);
	ft_putstr("\n\nChunk size       : ");
	ft_putnbr(file.chunk.size);
}

int	image(t_control *file)
{
	if (file->chunk.size == 0)
		return (ERR_IDAT);
	if (!file->info.chunk || file->info.iend)
		return (ERR_FORMAT);
	if (file->info.idat)
		return (ERR_HANDLED);
	file->info.idat = 1;
	if (file->verbose)
		verbose(*file);
	return (SUCCESS);
}
