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

int		big_endian4(unsigned char *nb)
{
	return ((nb[0] << 24) | (nb[1] << 16) | (nb[2] << 8) | (nb[3]));
}

int		big_endian2(unsigned char *nb)
{
	return ((nb[0] << 8) | (nb[1]));
}

int		is_power_two(int nb)
{
	return ((nb == 1 || nb == 2 || nb == 4 || nb == 8 || nb == 16 ? 1 : 0));
}
