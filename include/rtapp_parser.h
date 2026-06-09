/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:43:31 by sscheini          #+#    #+#             */
/*   Updated: 2026/06/09 17:36:59 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_PARSER_H
# define RTAPP_PARSER_H

# include "rtapp.h"
# include "g_parse_err_msgs.h"
# include <float.h>

# if BONUS
#  include "rtapp_parser_bonus.h"
# endif

/*--------------------------------------------------------------------------*/
/*--------------------------------STRUCTURES--------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Represents a closed range of valid double values for input validation.
 * @note Used by parse_double and parse_vector to validate that parsed
 * values fall within the expected range for each element parameter.
 */
typedef struct s_dlim
{
	double	min; // Minimum accepted value, inclusive.
	double	max; // Maximum accepted value, inclusive.
}	t_dlim;

/*--------------------------------------------------------------------------*/
/*-----------------------------ELEMENTS PARSERS-----------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Validates the arguments of a camera declaration.
 * @param arr The array of strings where arr[1] is position, arr[2] is
 * normal, and arr[3] is the FOV angle.
 * @param i The line number in the scene file, used for error logging.
 * @return RT_SUCCESS if all arguments are valid, RT_FAILURE otherwise.
 * @note Position accepts any double range. Normal components are validated
 * in the -1.0 to 1.0 range. FOV is validated in the 0 to 180 range.
 */
int				parse_camera(char **split, int i);

/**
 * Validates the arguments of an ambient light declaration.
 * @param split The array of strings containing the ambient light parameters,
 * where split[1] is the brightness ratio and split[2] is the RGB color.
 * @param i The line number in the scene file, used for error logging.
 * @return RT_SUCCESS if all arguments are valid, RT_FAILURE otherwise.
 * @note Ratio is validated in the 0.0 to 1.0 range. Color channels are
 * validated in the 0 to 255 range.
 */
int				parse_la(char **split, int i);

/**
 * Validates the arguments of a point light declaration.
 * @param split The array of strings containing the point light parameters,
 * where split[1] is position, split[2] is brightness, split[3] is color.
 * @param i The line number in the scene file, used for error logging.
 * @return RT_SUCCESS if all arguments are valid, RT_FAILURE otherwise.
 * @note Brightness is validated in the -1.0 to 1.0 range. Color channels
 * are validated in the 0 to 255 range. Only available in bonus mode.
 */
int				parse_lp(char **split, int i);

int				parse_quadric(char **arr, int i, const char *const *g_msgs);

/**
 * Validates the arguments of a sphere declaration.
 * @param arr The array of strings where arr[1] is position, arr[2] is
 * diameter, and arr[3] is the RGB color.
 * @param i The line number in the scene file, used for error logging.
 * @return RT_SUCCESS if all arguments are valid, RT_FAILURE otherwise.
 * @note Position accepts any double range. Diameter must be positive.
 * Color channels are validated in the 0 to 255 range.
 */
int				parse_sp(char **split, int i, const char *const *g_msgs);

/**
 * Validates the arguments of a plane declaration.
 * @param arr The array of strings where arr[1] is position, arr[2] is
 * normal, and arr[3] is the RGB color.
 * @param i The line number in the scene file, used for error logging.
 * @return RT_SUCCESS if all arguments are valid, RT_FAILURE otherwise.
 * @note Position accepts any double range. Normal components are validated
 * in the -1.0 to 1.0 range. Color channels in the 0 to 255 range.
 */
int				parse_pl(char **split, int i, const char *const *g_msgs);

/*--------------------------------------------------------------------------*/
/*-----------------------------PARSER UTILITIES-----------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Parses a single line of a scene file and initializes its element.
 * @param line The T_LIST node whose content is the raw scene file line.
 * @param i The line number in the scene file, used for error logging.
 * @param app The T_RTAPP instance to initialize the parsed element into.
 * @return RT_SUCCESS if the line was parsed and initialized successfully,
 * RT_FAILURE if splitting, dispatch lookup, or initialization fails.
 * @note Empty lines (starting with newline) are silently skipped.
 * The split array is always freed before returning.
 */
int				parse_line(t_list *line, int i, t_rtapp *app);

/**
 * Parses and validates a comma-separated vector string.
 * @param sp The element specifier string, used for error logging.
 * @param str The string to parse in "X,Y,Z" format.
 * @param i The line number in the scene file, used for error logging.
 * @param limits The T_DLIM containing the accepted range per component.
 * @return RT_SUCCESS if STR contains exactly three valid doubles within
 * limits, RT_FAILURE if splitting fails or any component is invalid.
 */
int				parse_vector(char *sp, char *str, int i, t_dlim limits);

/**
 * Parses and validates a string as a double within the given limits.
 * @param sp The element specifier string, used for error logging.
 * @param str The string to parse and validate as a double.
 * @param i The line number in the scene file, used for error logging.
 * @param limits The T_DLIM containing the accepted min and max range.
 * @return RT_SUCCESS if STR is a valid double within limits, RT_FAILURE
 * if STR is NULL, has more than one decimal point, or is out of range.
 */
int				parse_double(char *sp, char *str, int i, t_dlim limits);

t_dlim			build_limit(double min, double max);

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif