#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "png.h"

static void	check_sign(char *buffer)
{
	int				i;
	unsigned char	sign[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};

	i = -1;
	while (++i < 8)
		if ((unsigned char)buffer[i] != sign[i])
			clean(buffer, ERR_SIGN, 2);
}

static void	read_png(char *buffer, t_control file)
{
	int				i;
	t_process		handler[2] = {{NULL, NULL}};

	setup(&file, handler);
	check_sign(buffer);
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
