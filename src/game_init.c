#include "chunks.h"

int game_init_world(char*** world, size_t world_width, size_t world_height)
{
	assert(world != NULL);

	*world				= malloc(world_height * sizeof(char*));
	assert(*world != NULL);

	char* world_cells	= malloc(world_height * world_width);
	assert(world_cells != NULL);

	memset(world_cells, CELL_FREE, world_height*world_width);

	for(size_t i =0; i<world_height; i++)
		(*world)[i] = world_cells + world_width*i;

	return 0;
}

int game_init_universe(game_universe_t** universe, size_t world_width, size_t world_height, size_t cell_size)
{
	assert(universe != NULL);

	*universe = malloc(sizeof(game_universe_t));
	assert(*universe != NULL);

	memset(*universe, 0, sizeof(game_universe_t));

	(*universe)->world_height	= world_height;
	(*universe)->world_width	= world_width;

	(*universe)->cell_size		= cell_size;

	game_init_world(&((*universe)->world_0), world_width, world_height);
	game_init_world(&((*universe)->world_1), world_width, world_height);


	return 0;
}
