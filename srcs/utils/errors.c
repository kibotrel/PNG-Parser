#include "libft.h"
#include "macros.h"
#include "png.h"

static void	fill_messages(char **errors)
{
	int		i;

	i = -1;
	errors[++i] = "\033[32;1mSuccess :\033[0m PNG file correctly retrieved.\0";
	errors[++i] = "\033[31;1mError :\033[0m Can't allocate memory.\0";
	errors[++i] = "\033[31;1mError :\033[0m Can't open file.\0";
	errors[++i] = "\033[31;1mError :\033[0m Incorrect signature.\0";
	errors[++i] = "\033[31;1mError :\033[0m Incorrect IHDR chunk.\0";
	errors[++i] = "\033[31;1mError :\033[0m Incorrect image dimensions.\0";
	errors[++i] = "\033[31;1mError :\033[0m File is to large to be handled.\0";
	errors[++i] = "\033[31;1mError :\033[0m Incorrect bit depth.\0";
	errors[++i] = "\033[31;1mError :\033[0m Incorrect color type.\0";
	errors[++i] = "\033[31;1mError :\033[0m Wrong depth - colortype pair.\0";
	errors[++i] = "\033[31;1mError :\033[0m Incorrect IEND chunk.\0";
	errors[++i] = "\033[31;1mError :\033[0m Incorrect file structure.\0";
	errors[++i] = "\033[31;1mError :\033[0m Incorrect tIME chunk.\0";
	errors[++i] = "\033[31;1mError :\033[0m File date isn't well formated.\0";
	errors[++i] = "\033[31;1mError :\033[0m Incorrect IDAT chunk.\0";
	errors[++i] = "\033[31;1mError :\033[0m Settings not handled.\0";
}

int			process_state(t_control file, int code)
{
	char	*errors[NB_ERRORS + 1];

	if (file.info.chunk >= 1 || code == SUCCESS)
		ft_putchar('\n');
	else
		ft_putstr("\n\n");
	if (file.verbose)
		ft_putchar('\n');
	fill_messages(errors);
	ft_putendl(errors[code]);
	ft_putchar('\n');
	return (code);

}
