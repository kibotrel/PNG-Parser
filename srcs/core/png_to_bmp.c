/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_to_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:16:17 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/14 16:25:10 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "macros.h"
#include "png.h"

static void	read_png(char *buffer, t_control file)
{
	int				i;
	t_process		handler[2] = {{NULL, NULL}};

	setup(&file, handler);
	check_signature(buffer);
	while (file.info.position < file.size)
	{
		i = -1;
		ft_memcpy(file.chunk.length, buffer + file.info.position, 4);
		file.chunk.size = big_endian(file.chunk.length);
		fill_chunkname(file.chunk.name, buffer + file.info.position + 4, 4);
		while (handler[++i].type)
			if (!ft_strcmp(handler[i].type, file.chunk.name))
			{
				handler[i].process(buffer + file.info.position + 8, &file);
				break;
			}
		printf("%s\n", file.chunk.name);
		file.info.position += file.chunk.size + 12;
	}
	free(buffer);
}

void		png_to_bmp(char *png)
{
	FILE			*tmp;
	char			*buffer;
	t_control		file;

	if (!(buffer = (char*)malloc(MAX_SIZE)))
		ft_print_error(ERR_MALLOC, 1);
	if (!(tmp = fopen(png, "r")))
		clean(buffer, ERR_OPEN, 2);
	file.size = fread(buffer, sizeof(char), MAX_SIZE, tmp);
	if (file.size <= MAX_SIZE && feof(tmp) && !ferror(tmp) && !fclose(tmp))
		read_png(buffer, file);
	else
		clean(buffer, ERR_FILE, 6);
}
