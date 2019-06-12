#include "png.h"

int	main(int ac, char **av)
{
	if (ac == 2)
		png_to_bmp(av[1]);
}
