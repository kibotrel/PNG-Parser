/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:03:44 by kibotrel          #+#    #+#             */
/*   Updated: 2019/06/14 16:28:46 by kibotrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

/*
**	Useful macros
*/

# define MAX_SIZE	33554432
# define NB_CHUNKS	3

/*
**	Error codes
*/

# define ERR_END	"\033[31;1mError :\033[0m Incorrect IEND chunk."
# define ERR_DATE	"\033[31;1mError :\033[0m File date isn't well formated."
# define ERR_OPEN 	"\033[31;1mError :\033[0m Can't open file."
# define ERR_FILE	"\033[31;1mError :\033[0m File is to large to be handled."
# define ERR_SIZE	"\033[31;1mError :\033[0m Incorrect image dimensions."
# define ERR_SIGN 	"\033[31;1mError :\033[0m Incorrect signature."
# define ERR_TIME	"\033[31;1mError :\033[0m Incorrect tIME chunk."
# define ERR_COLOR	"\033[31;1mError :\033[0m Incorrect color type."
# define ERR_DEPTH	"\033[31;1mError :\033[0m Incorrect bit depth."
# define ERR_MALLOC "\033[31;1mError :\033[0m Can't allocate memory."
# define ERR_HEADER	"\033[31;1mError :\033[0m Incorrect IHDR chunk."
# define ERR_PRESET "\033[31;1mError :\033[0m Wrong bit depth - colortype pair."
# define ERR_FORMAT	"\033[31;1mError :\033[0m Incorrect file structure."

#endif
