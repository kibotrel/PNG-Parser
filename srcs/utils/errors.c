/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 04:53:54 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/25 17:18:32 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "macros.h"
#include "png.h"

void		is_valid_read(int size, int *out)
{
	if (size <= 0)
		*out = ERR_READ;
	else if (size >= MAX_SIZE)
		*out = ERR_FILE;
}

int			check_presets(unsigned char depth, unsigned char color)
{
	if (color == 3 && depth == 16)
		return (ERROR);
	else if ((color == 2 || color == 4 || color == 6) && depth < 8)
		return (ERROR);
	else
		return (SUCCESS);
}

static void	messages(char **errors)
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
	errors[++i] = "\033[31;1mError :\033[0m Can't read the given file.\0";
	errors[++i] = "\033[31;1mError :\033[0m Failed to retrieve image data\0";
	errors[++i] = "\033[31;1mError :\033[0m Can't close file\0";
}

int			output(t_control file, int code)
{
	char	*errors[NB_ERRORS + 1];

	(void)file;
	if (!code && file.verbose)
		ft_putstr("\n\n");
	else if ((!code && file.debug))
		ft_putchar('\n');
	else if (code == ERR_HANDLED && (file.verbose || file.debug))
		ft_putchar('\n');
	if (code == ERR_HANDLED && file.verbose)
		ft_putchar('\n');
	else if ((code == ERR_SIGN || code == ERR_OPEN) && !file.verbose)
		ft_putchar('\n');
	messages(errors);
	ft_putendl(errors[code]);
	ft_putchar('\n');
	return (code);
}
