/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:22 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/08 17:36:28 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_valid_point(t_game *game, t_point point, char target)
{
	if (point.x < 1 || point.y < 1
		|| point.x >= game->map.width - 1
		|| point.y >= game->map.height - 1)
		return (false);
	if (target == COLLECTIBLE)
	{
		if (game->map.map_str[point.y][point.x] == WALL
			|| game->map.map_str[point.y][point.x] == EXIT)
			return (false);
	}
	else if (target == EXIT)
	{
		if (game->map.map_str[point.y][point.x] == WALL)
			return (false);
	}
	return (true);
}

bool	is_target(t_game *game, char target, t_dfs *dfs)
{
	if (game->map.map_str[dfs->current.y][dfs->current.x] == target)
	{
		if (target == COLLECTIBLE)
			game->map.map_str[dfs->current.y][dfs->current.x] = CAN_GET_COIN;
		return (true);
	}
	return (false);
}

void	free_int_matrix(int **matrix, int height)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (i < height)
			free(matrix[i++]);
		free(matrix);
	}
}

void	free_dfs(t_dfs *dfs, t_game *game)
{
	free_stack(&dfs->stack);
	free_int_matrix(dfs->visited, game->map.height);
	free_int_matrix(dfs->direction, 4);
}

int	**basic_vector(int i, int **direction)
{
	if (i == 0)
	{
		direction[i][0] = 1;
		direction[i][1] = 0;
	}
	else if (i == 1)
	{
		direction[i][0] = 0;
		direction[i][1] = 1;
	}
	else if (i == 2)
	{
		direction[i][0] = -1;
		direction[i][1] = 0;
	}
	else if (i == 3)
	{
		direction[i][0] = 0;
		direction[i][1] = -1;
	}
	return (direction);
}
