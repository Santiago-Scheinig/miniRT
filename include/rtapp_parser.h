/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtapp_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:43:31 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/12 20:43:42 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTAPP_PARSER_H
# define RTAPP_PARSER_H

# include "rtapp.h"
# include <float.h>

/*--------------------------------------------------------------------------*/
/*----------------------------------GLOBAL----------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Error message arrays for argument validation of each scene element.
 * @note Each array follows the convention: entries 0 to n-1 correspond
 * to missing argument errors in declaration order, and the last entry
 * is the excess arguments error. Used by parse_arg to validate input.
 */
extern const char	*const g_la_msgs[]; // Ambient light parser messages.
extern const char	*const g_lp_msgs[]; // Point light parser messages.
extern const char	*const g_ca_msgs[]; // Camera parser messages.
extern const char	*const g_pl_msgs[]; // Plane parser messages.
extern const char	*const g_cy_msgs[]; // Cylinder parser messages.
extern const char	*const g_sp_msgs[]; // Sphere parser messages.

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
 * Validates the arguments of a point light declaration.
 * @param split The array of strings containing the point light parameters,
 * where split[1] is position, split[2] is brightness, split[3] is color.
 * @param i The line number in the scene file, used for error logging.
 * @return RT_SUCCESS if all arguments are valid, RT_FAILURE otherwise.
 * @note Brightness is validated in the -1.0 to 1.0 range. Color channels
 * are validated in the 0 to 255 range. Only available in bonus mode.
 */
int				parse_lp(char **split, int i);

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
 * Validates the arguments of a plane declaration.
 * @param arr The array of strings where arr[1] is position, arr[2] is
 * normal, and arr[3] is the RGB color.
 * @param i The line number in the scene file, used for error logging.
 * @return RT_SUCCESS if all arguments are valid, RT_FAILURE otherwise.
 * @note Position accepts any double range. Normal components are validated
 * in the -1.0 to 1.0 range. Color channels in the 0 to 255 range.
 */
int				parse_pl(char **split, int i);

/**
 * Validates the arguments of a cylinder declaration.
 * @param arr The array of strings where arr[1] is position, arr[2] is
 * normal, arr[3] is diameter, arr[4] is height, and arr[5] is RGB color.
 * @param i The line number in the scene file, used for error logging.
 * @return RT_SUCCESS if all arguments are valid, RT_FAILURE otherwise.
 * @note Normal components are validated in the -1.0 to 1.0 range.
 * Diameter and height must be positive. Color channels in 0 to 255 range.
 */
int				parse_cy(char **split, int i);

/**
 * Validates the arguments of a sphere declaration.
 * @param arr The array of strings where arr[1] is position, arr[2] is
 * diameter, and arr[3] is the RGB color.
 * @param i The line number in the scene file, used for error logging.
 * @return RT_SUCCESS if all arguments are valid, RT_FAILURE otherwise.
 * @note Position accepts any double range. Diameter must be positive.
 * Color channels are validated in the 0 to 255 range.
 */
int				parse_sp(char **split, int i);

/*--------------------------------------------------------------------------*/
/*-----------------------------PARSER UTILITIES-----------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Validates that a string array has the expected number of arguments.
 * @param arr The NULL-terminated array of strings to validate, where
 * arr[0] is the element specifier and arr[1..n] are its parameters.
 * @param i The line number in the scene file, used for error logging.
 * @param msgs The error message array where msgs[0..expected-1] are
 * missing argument errors and msgs[expected] is the excess error.
 * @param expected The exact number of arguments expected after arr[0].
 * @return RT_SUCCESS if ARR has exactly EXPECTED arguments, RT_FAILURE
 * with the appropriate message if any argument is missing or excess.
 */
int				parse_arg(char **arr, int i, const char **msgs, int expected);

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

/*--------------------------------------------------------------------------*/
/*------------------------------------END-----------------------------------*/
/*--------------------------------------------------------------------------*/

#endif