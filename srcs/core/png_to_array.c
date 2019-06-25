/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:16:17 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/25 19:56:40 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "macros.h"
#include "png.h"

static void	parse_png(t_control *file, int *out)
{
	file->debug ? print_chunks(*file) : 0;
	*out = check_signature(file->save);
	while (!*out && file->info.pos < file->size)
	{
		ft_memcpy(file->chunk.length, file->save + file->info.pos, 4);
		file->chunk.size = big_endian4(file->chunk.length);
		get_chunkname(file->chunk.name, file->save + file->info.pos + 4, 4);
		*out = selector(file);
		file->info.pos += file->chunk.size + 12;
	}
}

int			png_to_array(char *png, t_png *image, int flag)
{
	int			fd;
	int			out;
	t_control	file;

	setup(&file, image, flag);
	flag_mode(file.verbose, file.debug);
	if (!(file.save = (unsigned char*)malloc(MAX_SIZE)))
		out = ERR_MALLOC;
	else if ((fd = open(png, O_RDONLY)) < 0)
		out = ERR_OPEN;
	else
	{
		file.size = read(fd, file.save, MAX_SIZE);
		is_valid_read(file.size, &out);
		if (!close(fd))
			parse_png(&file, &out);
		else
			out = ERR_CLOSE;
		!out ? set_array(&file, image) : 0;
	}
	out != ERR_MALLOC ? free(file.save) : 0;
	file.debug ? print_state(file, out) : 0;
	return (output(file, out));
}
