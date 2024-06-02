#include "so_long.h"

// check if can clear map dfs
void	clear_check_map(t_game *game)
{
	int		can_get_coin;

	can_get_coin = 0;
	while (can_get_coin < game->map.total_coin)
	{
		if (dfs(game, game->player.point, COLLECTIBLE) == false)
			error_and_exit("Invalid map", "collectible is not reachable", game);
		can_get_coin++;
	}
	if (dfs(game, game->player.point, EXIT) == false)
		error_and_exit("Invalid map", "exit is not reachable", game);
}

void	map_init(t_game *game)
{
	int		width;
	int		height;

	height = 0;
	while (height < game->map.height)
	{
		width = 0;
		while (width < game->map.width)
		{
			put_image(game, game->map.map[height][width], width, height);
			width++;
		}
		height++;
	}
}
