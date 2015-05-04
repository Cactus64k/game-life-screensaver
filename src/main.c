#include "chunks.h"

gboolean event_cb(GtkWidget* widget, GdkEvent* event, gpointer user_data);

int main(int argc,	char *argv[])
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	setlocale(LC_ALL, "");

	char* domain = textdomain(PACKAGE_NAME);
	assert(domain != NULL);

	bind_textdomain_codeset(PACKAGE_NAME, "UTF-8");
	textdomain(PACKAGE_NAME);

	gint update_rate	= 100;
	gint cell_size		= 4;
	gboolean print_version = FALSE;

	GOptionEntry cmd_options[]	= {
									{"update-rate",	'u',	0,	G_OPTION_ARG_INT,	&update_rate,	_C("Update rate in msec"),	"100"},
									{"cell_size",	'c',	0,	G_OPTION_ARG_INT,	&cell_size,		_C("Cell size"),			"8"},
									{"version",		'v',	0,	G_OPTION_ARG_NONE, 	&print_version,	_C("Print version"),		NULL},
									{NULL}
								};


	GError *error				= NULL;

	GOptionContext *cmd_context	= g_option_context_new(NULL);
	g_option_context_set_help_enabled(cmd_context, TRUE);
	g_option_context_add_main_entries(cmd_context, cmd_options, NULL);


	gchar **cmd_line = g_strdupv(argv);
	gint cmd_count = argc;

	if(g_option_context_parse(cmd_context, &cmd_count, &cmd_line, &error) == FALSE)
	{
		fprintf(stderr, _C("ERROR: %s\n\n"), error->message);

		g_error_free(error);
	}
	else
	{
		if(print_version == TRUE)
		{
			printf("game-life: %s\n", PACKAGE_VERSION);
		}
		else
		{
			gtk_init(&argc, &argv);

			GdkScreen* default_screen	= gdk_screen_get_default();
			gint screen_height			= gdk_screen_get_height(default_screen);
			gint screen_width			= gdk_screen_get_width(default_screen);

			size_t world_height			= screen_height / (cell_size +1);
			size_t world_width			= screen_width / (cell_size +1);

			game_universe_t* universe = NULL;

			game_init_universe(&universe, world_width,  world_height, cell_size);
			game_set_random(universe);

			GtkWidget* main_wnd	= gtk_window_new(GTK_WINDOW_TOPLEVEL);
			GdkWindow* root_wnd	= gdk_screen_get_root_window(default_screen);
			gtk_widget_set_window(main_wnd, root_wnd);
			//gtk_window_fullscreen(GTK_WINDOW(main_wnd));
			gtk_widget_set_app_paintable(main_wnd, TRUE);

			g_signal_connect(main_wnd, "destroy", G_CALLBACK(gtk_main_quit),  NULL);
			g_signal_connect(main_wnd, "event", G_CALLBACK(event_cb),  NULL);
			g_signal_connect(main_wnd, "draw", G_CALLBACK(draw_cb),  universe);


			const char* remote_wnd_env = getenv("XSCREENSAVER_WINDOW");
			if(remote_wnd_env != NULL)	// FIXME what is this shit? i dont know
			{
				char* end = NULL;
				Window remote_wnd			= (Window)strtol(remote_wnd_env, &end, 0);
				GdkDisplay* default_display	= gdk_display_get_default();
				GdkWindow* window			= gdk_x11_window_foreign_new_for_display(default_display, remote_wnd);

				//GtkStyle* main_wnd_style	= gtk_widget_get_style(main_wnd);
				//gtk_style_set_background(main_wnd_style, window, GTK_STATE_NORMAL);

				gtk_widget_set_window(main_wnd, window);
				gtk_widget_set_realized(main_wnd, TRUE);

				gtk_window_resize(GTK_WINDOW(main_wnd), screen_width, screen_height);
			}


			gtk_widget_show_all(main_wnd);

			g_timeout_add(update_rate, update_image, main_wnd);

			gtk_main();
		}
	}

	g_option_context_free(cmd_context);

	g_strfreev(cmd_line);

	return 0;
}

gboolean event_cb(GtkWidget* widget, GdkEvent* event, gpointer user_data)
{
	if((event->type == GDK_KEY_PRESS) || (event->type == GDK_MOTION_NOTIFY))
	{
		gtk_main_quit();
		return TRUE;
	}
	return FALSE;
}
