#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "zlib.h"
#include "libft.h"
#include "macros.h"
#include "png.h"

static void	verbose(t_control file)
{
	chunk_infos(file.chunk.name, file.chunk.size);
}

static int	get_raw_chunk(t_control *file)
{
	z_stream		z;

	if (!(file->raw = (unsigned char*)malloc(file->info.raw + 1)))
		return (ERR_MALLOC);
	z.zalloc = Z_NULL;
	z.zfree = Z_NULL;
	z.opaque = Z_NULL;
	z.avail_in = file->chunk.size;
	z.next_in = (Bytef*)file->stream;
	z.avail_out = file->info.raw;
	z.next_out = (Bytef*)file->raw;
	inflateInit2_(&z, 15, ZLIB_VERSION, sizeof(z));
	inflate(&z, Z_NO_FLUSH);
	inflateEnd(&z);
	return (SUCCESS);
}

static void	print_memory(t_control file)
{
	char			base[16] = "0123456789ABCDEF";
	unsigned int	i;

	i = 0;
	ft_putstr("\nChunk data       : ");
	while(i < file.info.raw)
	{
		ft_putchar(base[file.raw[i] / 16]);
		ft_putchar(base[file.raw[i] % 16]);
		ft_putchar(' ');
		if (!(++i % file.info.scanline))
			ft_putstr("\n                   ");
	}
}

int			image(t_control *file)
{
	if (file->chunk.size == 0)
		return (ERR_IDAT);
	if (!file->info.chunk || file->info.iend)
		return (ERR_FORMAT);
	if (file->info.idat)
		return (ERR_HANDLED);
	file->info.idat = 1;
	file->verbose ? verbose(*file) : 0;
	if (!(file->stream = (unsigned char*)ft_strnew(IDAT_BUFFER)))
		return (ERR_MALLOC);
	ft_memcpy(file->stream, file->save + file->info.pos + 8, file->chunk.size);
	get_raw_chunk(file);
	{
		file->verbose ? print_memory(*file) : 0;
	}
	free(file->stream);
	return (SUCCESS);
}
