/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signature.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:10:40 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/25 19:17:21 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macros.h"

int	check_signature(unsigned char *buffer)
{
	int				i;
	static char		sign[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};

	i = -1;
	while (++i < 8)
		if (buffer[i] != (unsigned char)sign[i])
			return (ERR_SIGN);
	return (SUCCESS);
}
