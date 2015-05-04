#include "chunks.h"

int game_set_random(game_universe_t* universe)
{
	GRand* rand = g_rand_new();

	size_t height	= universe->world_height;
	size_t width	= universe->world_width;

	char** world_0	= universe->world_0;

	for(size_t y=1; y<height-1; y++)
		for(size_t x=1; x<width-1; x++)
			world_0[y][x] = (g_rand_int(rand)%12)? CELL_FREE: CELL_ALIVE;

	g_rand_free(rand);

	universe->generation = 0;

	return 0;
}

int game_set_frame(game_universe_t* universe)
{
	GRand* rand = g_rand_new();

	size_t height	= universe->world_height;
	size_t width	= universe->world_width;

	char** world_0	= universe->world_0;

	memset(world_0[0], CELL_ALIVE, width);
	memset(world_0[height-1], CELL_ALIVE, width);

	for(size_t y=0; y<height; y++)
	{
		world_0[y][0] = CELL_ALIVE;
		world_0[y][width-1] = CELL_ALIVE;
	}

	g_rand_free(rand);

	universe->generation = 0;

	return 0;
}

int game_set_r_pentomino(game_universe_t* universe, size_t pos_x, size_t pos_y)
{

	size_t height	= universe->world_height;
	size_t width	= universe->world_width;

	if(pos_y > 2 && pos_y -2 < height)
	{
		if(pos_x +2 < width)
		{
			char** world_0	= universe->world_0;

			world_0[pos_y+0][pos_x+0]	= CELL_FREE;
			world_0[pos_y+0][pos_x+1]	= CELL_ALIVE;
			world_0[pos_y+0][pos_x+2]	= CELL_ALIVE;

			world_0[pos_y+1][pos_x+0]	= CELL_ALIVE;
			world_0[pos_y+1][pos_x+1]	= CELL_ALIVE;
			world_0[pos_y+1][pos_x+2]	= CELL_FREE;

			world_0[pos_y+2][pos_x+0]	= CELL_FREE;
			world_0[pos_y+2][pos_x+1]	= CELL_ALIVE;
			world_0[pos_y+2][pos_x+2]	= CELL_FREE;
		}
	}

	universe->generation = 0;

	return 0;
}
