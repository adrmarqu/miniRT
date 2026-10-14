/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:10:35 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/11/22 14:32:10 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	delete_newline(char *line)
{
	int		len;
	int		i;

	len = ft_strlen(line);
	if (!len)
		return (0);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i] || line[i] == '#' || line[i] == '\n')
		return (0);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (1);
}

static int	init_scene_null(t_scene *scene)
{
	scene->light = NULL;
	scene->camera = NULL;
	scene->ambient = NULL;
	scene->obj = NULL;
	return (0);
}

static int	read_data(int fd, t_scene *scene)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (delete_newline(line) && set_data(scene, line))
			return (free(line), 1);
		free(line);
	}
	while (scene->obj && scene->obj->prev)
		scene->obj = scene->obj->prev;
	while (scene->light && scene->light->prev)
		scene->light = scene->light->prev;
	if (!scene->ambient)
		return (error_parser(YEL, MSG_AMB), 1);
	if (!scene->camera)
		return (error_parser(YEL, MSG_CAM), 1);
	if (!scene->light)
		return (error_parser(YEL, MSG_LIGHT), 1);
	while (scene->obj && scene->obj->prev)
		scene->obj = scene->obj->prev;
	return (0);
}

static int	ft_open_file(char *name)
{
	int	fd;
	int	len;

	if (!name)
		return (error_parser(YEL, MSG_FEW), -1);
	len = ft_strlen(name);
	if (len < 4 || ft_strncmp(name + len - 3, ".rt", 3) != 0)
		return (error_parser(YEL, MSG_EXT), -1);
	if (name[len - 4] == '/')
		return (error_parser(YEL, MSG_EXT), -1);
	if ((len == 4 && !ft_strncmp(name, "..rt", 4))
		|| (len >= 5 && !ft_strncmp(name + len - 5, "/..rt", 5)))
		return (error_parser(YEL, MSG_EXT), -1);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (error_parser(YEL, MSG_OPEN), -1);
	return (fd);
}

int	read_file(int ac, char *file, t_scene *scene)
{
	int	fd;

	init_scene_null(scene);
	if (ac < 2)
		return (error_parser(YEL, MSG_FEW), 1);
	else if (ac > 2)
		return (error_parser(YEL, MSG_TOO), 1);
	fd = ft_open_file(file);
	if (fd == -1)
		return (1);
	if (read_data(fd, scene))
	{
		close(fd);
		free_scene(scene);
		return (1);
	}
	close(fd);
	return (0);
}
