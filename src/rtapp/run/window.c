/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 19:01:10 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/14 19:14:10 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtapp.h"

static void set_hooks()
{
	//set the esc and cross exit hooks though i think they are set by default
}

static void replace_image(uint32_t *image, /*pointer to the minilib img*/)
{
	//free the uint32_t * inside of the img of minilib
	//replace it with our own img
}

//returns NULL on error
int window_run(uint32_t *image)
{
	//variable minilib_instance;

	//minilib_instance = minilib_initalization_instance function();
	//set_hooks(); Not sure this is needed since i think the cross and esc exit are already imbued on the minilib instance
	//create_image(); I think this is just the minilib function to create an image
	//replace_image(minilib_instance);
	//return(minilib_instance); returns the pointer of the instance with the image created and already updated
}

int window_kill(/*variable of minilib instance*/)
{
	//function of minilib to kill an image;
	//funciton of minilib to kill the instance;
}
