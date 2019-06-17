/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:08:51 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/14 16:08:52 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		big_endian4(char *length)
{
	return (((unsigned char)length[0] << 24)
		| ((unsigned char)length[1] << 16)
		| ((unsigned char)length[2] << 8)
		| ((unsigned char)length[3]));
}

int		big_endian2(char *length)
{
	return (((unsigned char)length[0] << 8)
		| ((unsigned char)length[1]));
}

int		is_power_two(int nb)
{
	return ((nb == 1 || nb == 2 || nb == 4 || nb == 8 || nb == 16 ? 1 : 0));
}
