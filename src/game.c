#include "chunks.h"

int game_update_universe(game_universe_t* universe)
{
	assert(universe != NULL);
	size_t world_height	= universe->world_height;
	size_t world_width	= universe->world_width;

	char** world_0		= universe->world_0;
	char** world_1		= universe->world_1;


	for(size_t y=0; y<world_height; y++)
	{
		for(size_t x=0; x<world_width; x++)
		{
			size_t alive_count = 0;

			for(ssize_t k=-1; k<=1; k++)
			{
				if(y != 0 || k != -1)		// для верхних строк
				{
					if(y+k != world_height)	// для нижних строк
					{
						if((x != 0)				&& (world_0[y+k][x-1] == CELL_ALIVE))
							alive_count++;

						if((k != 0)				&& (world_0[y+k][x-0] == CELL_ALIVE))		// центральную ячейку не считаем (0; 0)
							alive_count++;

						if((x+1 < world_width)	&& (world_0[y+k][x+1] == CELL_ALIVE))
							alive_count++;
					}
				}
			}

			if(alive_count > 3 || alive_count < 2)
			{
				if(world_0[y][x] == CELL_ALIVE)
					world_1[y][x] = CELL_DEAD;
				else
					world_1[y][x] = world_0[y][x];
			}
			else if(alive_count == 3)
				world_1[y][x] = CELL_ALIVE;
			else if(alive_count == 2)
				world_1[y][x] = world_0[y][x];
		}
	}

	void* ptr = universe->world_0;
	universe->world_0 = universe->world_1;
	universe->world_1 = ptr;

	universe->generation++;

	return 0;
}

gboolean update_image(void* arg)
{
	gtk_widget_queue_draw(GTK_WIDGET(arg));
	return TRUE;
}

gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	game_universe_t* universe = (game_universe_t*)data;

	if(universe->generation > 2000)
		game_set_random(universe);

	size_t world_height	= universe->world_height;
	size_t world_width	= universe->world_width;

	size_t cell_size	= universe->cell_size;

	char** world_0		= universe->world_0;

	cairo_set_source_rgb(cr, 0.3, 0.3, 0.3);
	cairo_paint(cr);

	cairo_set_source_rgb(cr, 0.35, 0.35, 0.35);
	cairo_set_line_width(cr, 1);

	for(size_t y =0; y<=world_height; y++)
	{
		cairo_move_to(cr, 0, y*(cell_size+1));
		cairo_line_to(cr, world_width*(cell_size+1), y*(cell_size+1));
		cairo_stroke(cr);
	}

	for(size_t x =0; x<=world_width; x++)
	{
		cairo_move_to(cr, x*(cell_size+1), 0);
		cairo_line_to(cr, x*(cell_size+1), world_height*(cell_size+1));
		cairo_stroke(cr);
	}

	for(size_t y =0; y<world_height; y++)
	{
		for(size_t x =0; x<world_width; x++)
		{
			if(world_0[y][x] == CELL_ALIVE)
			{
				cairo_set_source_rgb(cr, 0.42, 0.65, 0.80);
				cairo_rectangle(cr, x*(cell_size+1), y*(cell_size+1), cell_size, cell_size);
				cairo_fill(cr);
			}

			if(world_0[y][x] == CELL_DEAD)
			{
				cairo_set_source_rgb(cr, 0.36, 0.36, 0.36);
				cairo_rectangle(cr, x*(cell_size+1), y*(cell_size+1), cell_size, cell_size);
				cairo_fill(cr);
			}
		}
	}

	char buff[256];
	snprintf(buff, sizeof(buff)-1, "gen: %zu", universe->generation);

	cairo_set_font_size(cr, 15);
	cairo_move_to(cr, 10, 20);
	cairo_set_source_rgb(cr, 0.42, 0.65, 0.80);
	cairo_show_text(cr, buff);

	game_update_universe(universe);

	return TRUE;
}

