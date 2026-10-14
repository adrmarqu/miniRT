/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:46:40 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/11/23 13:31:02 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include <stdlib.h>

void	free_lights(t_light *light)
{
	void	*next;

	while (light && light->prev)
		light = light->prev;
	while (light)
	{
		next = light->next;
		free(light);
		light = next;
	}
}

void	free_objects(t_obj *obj)
{
	t_obj	*next;

	if (!obj)
		return ;
	while (obj->prev)
		obj = obj->prev;
	while (obj)
	{
		next = obj->next;
		if (obj->shape.sp)
			free(obj->shape.sp);
		free(obj);
		obj = next;
	}
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->ambient)
	{
		free(scene->ambient);
		scene->ambient = NULL;
	}
	if (scene->camera)
	{
		free(scene->camera);
		scene->camera = NULL;
	}
	if (scene->light)
	{
		free_lights(scene->light);
		scene->light = NULL;
	}
	if (scene->obj)
	{
		free_objects(scene->obj);
		scene->obj = NULL;
	}
}
