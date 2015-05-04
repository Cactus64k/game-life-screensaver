#ifndef GAME_LIFE_SCREENSAVER_SRC_CHUNKS_H_
#define GAME_LIFE_SCREENSAVER_SRC_CHUNKS_H_

	#include <stdlib.h>
	#include <stdio.h>
	#include <memory.h>
	#include <math.h>
	#include <stddef.h>
	#include <sys/types.h>
	#include <locale.h>
	#include <assert.h>
	#include <libintl.h>
	#include <gtk/gtk.h>
	#include <X11/X.h>
	#include <gdk/gdkx.h>

	#define CELL_ALIVE '+'
	#define CELL_FREE ' '
	#define CELL_DEAD '-'

	#define PACKAGE_VERSION "1.0.0"
	#define PACKAGE_NAME "game-life"

	#define _C(str) gettext(str)

	gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data);

	typedef struct game_universe_t
	{
		char** world_0;
		char** world_1;

		size_t world_height;
		size_t world_width;

		size_t cell_size;

		size_t generation;
	} game_universe_t;

	int game_init_universe			(game_universe_t** universe, size_t world_width, size_t world_height, size_t cell_size);
	int game_free_universe			(game_universe_t* universe);

	int game_set_random				(game_universe_t* universe);
	int game_set_frame				(game_universe_t* universe);
	int game_set_r_pentomino		(game_universe_t* universe, size_t pos_x, size_t pos_y);

	int game_set_small_space_ship	(game_universe_t* universe, size_t pos_x, size_t pos_y);
	gboolean update_image			(void* arg);

#endif /* GAME_LIFE_SCREENSAVER_SRC_CHUNKS_H_ */
