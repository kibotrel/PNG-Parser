/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 04:53:50 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/25 17:18:01 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "png.h"

void	print_chunk_basics(char *name, int size)
{
	ft_putstr("Chunk name       : ");
	ft_putstr(name);
	ft_putstr("\n\nChunk size       : ");
	ft_putnbr(size);
}

void	print_memory(t_control file, int state)
{
	static char		base[16] = "0123456789ABCDEF";
	unsigned int	i;

	i = 0;
	if (!state)
		ft_putstr("\nChunk data       : Inflated\n\n\t\t   ");
	else
		ft_putstr("                   Unfiltered\n\n\t\t   ");
	while (i < file.info.raw)
	{
		ft_putchar(base[file.raw[i] / 16]);
		ft_putchar(base[file.raw[i] % 16]);
		ft_putchar(' ');
		if (!(++i % file.info.scanline))
			ft_putstr("\n                   ");
	}
	ft_putchar('\n');
}

void	flag_mode(int verbose, int debug)
{
	if (verbose)
		ft_putendl("\n--- Verbose mode ---\n");
	else if (debug)
		ft_putendl("\n--- Debug mode ---\n");
}

void	print_chunks(t_control file)
{
	ft_putendl("Chunks :\n");
	while (file.info.pos < file.size)
	{
		ft_memcpy(file.chunk.length, file.save + file.info.pos, 4);
		file.chunk.size = big_endian4(file.chunk.length);
		get_chunkname(file.chunk.name, file.save + file.info.pos + 4, 4);
		ft_putendl((char*)file.chunk.name);
		file.info.pos += file.chunk.size + 12;
	}
}

void	print_state(t_control file, int code)
{
	if (!ft_strcmp(file.chunk.name, "IHDR"))
		ft_putchar('\n');
	ft_putstr("PNG Parser exit with code ");
	ft_putnbr(code);
	if (*file.chunk.name)
	{
		ft_putstr(" on chunk ");
		ft_putstr(file.chunk.name);
	}
	ft_putstr(".\n");
}
