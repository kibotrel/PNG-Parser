#include "libft.h"

void	chunk_infos(unsigned char *name, int size)
{
	if (ft_strcmp((char*)name, "IHDR"))
		ft_putchar('\n');
	if (ft_strcmp((char*)name, "IEND"))
		ft_putchar('\n');
	ft_putstr("Chunk name       : ");
	ft_putstr((char*)name);
	ft_putstr("\n\nChunk size       : ");
	ft_putnbr(size);
}
