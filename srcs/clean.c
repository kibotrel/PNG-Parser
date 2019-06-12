#include <stdlib.h>
#include "libft.h"

void	clean(char *buffer, char *error, int code)
{
	free(buffer);
	ft_print_error(error, code);
}
