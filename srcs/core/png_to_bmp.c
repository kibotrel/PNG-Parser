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

static void	read_png(t_control *file, char *save)
{
	int				i;
	t_process		handler[NB_CHUNKS + 1] = {{NULL, NULL}};

	setup(file, handler);
	check_signature(save);
	while (file->info.position < file->size)
	{
		i = -1;
		ft_memcpy(file->chunk.length, save + file->info.position, 4);
		file->chunk.size = big_endian4(file->chunk.length);
		fill_chunkname(file->chunk.name, save + file->info.position + 4, 4);
		while (handler[++i].type)
			if (!ft_strcmp(handler[i].type, file->chunk.name))
			{
				handler[i].process(file);
				break;
			}
		!file->verbose ? printf("%s\n", file->chunk.name) : 0;
		file->info.position += file->chunk.size + 12;
	}
	free(file->save);
}

void		png_to_bmp(char *png, char *flag)
{
	FILE			*tmp;
	t_control		file;

	if (!(file.save = (char*)malloc(MAX_SIZE)))
		ft_print_error(ERR_MALLOC, 1);
	if (!(tmp = fopen(png, "r")))
		clean(file.save, ERR_OPEN, 2);
	file.size = fread(file.save, sizeof(char), MAX_SIZE, tmp);
	if (flag)
		file.verbose = (!ft_strcmp(flag, "-v") ? 1 : 0);
	if (file.size <= MAX_SIZE && feof(tmp) && !ferror(tmp) && !fclose(tmp))
		read_png(&file, file.save);
	else
		clean(file.save, ERR_FILE, 6);
}
