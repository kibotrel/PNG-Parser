/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:03:44 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/25 17:10:13 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
**	Useful macros
*/

# define ON				1
# define OFF			0
# define ERROR			1
# define DEBUG			2
# define SUCCESS		0
# define VERBOSE		1
# define MAX_SIZE		33554432
# define NB_CHUNKS		3
# define NB_ERRORS		18
# define IDAT_BUFFER	8388608

/*
**	Error codes
*/

# define ERR_OPEN		2
# define ERR_IHDR		4
# define ERR_SIGN 		3
# define ERR_SIZE		5
# define ERR_FILE		6
# define ERR_IEND		10
# define ERR_TIME		12
# define ERR_DATE		13
# define ERR_IDAT		14
# define ERR_READ		16
# define ERR_DEPTH		7
# define ERR_COLOR		8
# define ERR_IMAGE		17
# define ERR_CLOSE		18
# define ERR_MALLOC		1
# define ERR_PRESET		9
# define ERR_FORMAT		11
# define ERR_HANDLED	15

#endif
