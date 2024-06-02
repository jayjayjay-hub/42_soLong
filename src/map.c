#include "so_long.h"

static void	check_rectangular(int first_line_len, int line_len, t_game *game)
{
	if (first_line_len != line_len)
		error_and_exit("Invalid map", "map width size is not rectangular", game);
}

static void	check_height(int height, t_game *game)
{
	if (height < 3)
		error_and_exit("Invalid map", "map height size must be 2 or more", game);
	if (height > MAX_HEIGHT_IMAGE)
	{
		error_and_exit("Invalid map", "map height size is too big", game);
	}
}

static void check_width(int width, t_game *game)
{
	if (width < 3)
		error_and_exit("Invalid map", "map width size must be 2 or more", game);
	if (width > MAX_WIDTH_IMAGE)
	{
		error_and_exit("Invalid map", "map width size is too big", game);
	}
}

static int	strlen_double_ptr(char **str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	return len;
}

static void	check_map(char **map, t_game *game)
{
	int		height;
	int		width;
	char	map_c;

	game->map_height = strlen_double_ptr(map);
	game->map_width = (int)ft_strlen(map[0]);
	check_width(game->map_width, game);
	height = -1;
	while (map[++height])
	{
		width = -1;
		while (map[height][++width])
		{
			map_c = map[height][width];
			if ((height == 0 || height == game->map_height - 1 || width == 0 || width == game->map_width - 1) && map_c != WALL)
				error_and_exit("Invalid map", "map must be closed/surrounded by walls.", game);
			if (map_c != EMPTY && map_c != WALL && map_c != COLLECTIBLE && map_c != EXIT && map_c != PLAYER)
				error_and_exit("Invalid map", "map must contain only 0, 1, C, E, and P", game);
		}
		check_rectangular((int)ft_strlen(map[0]), width, game);
	}
	check_height(height, game);
	game->window_width = width * IMAGE_SIZE;
	game->window_height = height * IMAGE_SIZE;
}

static void	get_map(int fd, t_game *game)
{
	char	*map_str;
	ssize_t read_bytes;

	map_str = malloc(sizeof(char) * READ_SIZE);
	if (!map_str)
		error_and_exit("Error: Malloc error", NULL, game);
	read_bytes = read(fd, map_str, READ_SIZE);
	if (read_bytes < 0)
		error_and_exit("Error: Read error", NULL, game);
	if (read_bytes >= MAX_READ_SIZE)
		error_and_exit("Error: Map is too big", NULL, game);
	map_str[read_bytes] = '\0';
	game->map = ft_split(map_str, '\n');
	if (!game->map)
		error_and_exit("Error: Split error", NULL, game);
	free(map_str);
}

// check if can clear map dfs
// void	clear_check_map(char **map, t_game *game)
// {
// }

void	window_init(t_game *game, char *map_file_path)
{
	int	fd;

	fd = open(map_file_path, O_RDONLY);
	if (fd < 0)
		error_and_exit("Invalid map file", "failed to open map file", game);
	if (ft_strnstr(map_file_path, ".ber", ft_strlen(map_file_path)) == NULL)
		error_and_exit("Invalid map file", "file extension must be .ber", game);
	get_map(fd, game);
	close(fd);
	check_map(game->map, game);
	// clear_check_map(game->map, game);
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, game->window_width, game->window_height, "so_long");
}

void	map_init(t_game *game)
{
	int		width;
	int		height;

	height = 0;
	while (height < game->map_height)
	{
		width = 0;
		while (width < game->map_width)
		{
			if (game->map[height][width] == PLAYER)
			{
				game->player.x = width;
				game->player.y = height;
			}
			if (game->map[height][width] == COLLECTIBLE)
				game->total_collectibles++;
			put_image(game, game->map[height][width], width, height);
			width++;
		}
		height++;
	}
}
