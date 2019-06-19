#include <stdio.h>
#include <stdlib.h>
#include "png.h"

int	main(int ac, char **av)
{
	int	flag;
	
	if (ac > 1)
	{
		if (av[2])
			flag = atoi(av[2]);
		else
			flag = 0;
		png_to_array(av[1], flag);
	}
}
