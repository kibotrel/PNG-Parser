#include "png.h"

int	main(int ac, char **av)
{
	if (ac > 1)
		png_to_bmp(av[1], av[2]);
}
