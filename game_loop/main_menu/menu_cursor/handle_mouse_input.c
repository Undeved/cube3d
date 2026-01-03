#include "../../../cube.h"

// added after push
static void	play_sound_if_index_changed(t_parsed_data *pd)
{
	static int	last_index[2] = {-1, -1};

	if (pd->chars_menu.button_index != last_index[0])
	{
		play_sound_once(pd, "sound/button_hover.mp3");
		last_index[0] = pd->chars_menu.button_index;
	}
	if (pd->menu.button_index != last_index[1])
	{
		play_sound_once(pd, "sound/button_hover.mp3");
		last_index[1] = pd->menu.button_index;
	}
}

static bool	within_bounds(t_pos m_pos, t_pos img_pos, int width, int height)
{
	(void)width;
	(void)height;
	if (m_pos.x < (img_pos.x + width - TRN_OFST)
		&& m_pos.y < (img_pos.y + height - TRN_OFST)
		&& m_pos.x >= (img_pos.x + TRN_OFST)
		&& m_pos.y >= (img_pos.y + TRN_OFST))
		return (true);
	return (false);
}

static void	main_menu_buttons(double xpos, double ypos, t_parsed_data *pd)
{
	if (within_bounds((t_pos){xpos, ypos},
		(t_pos){START_BUTTON_X,
		START_BUTTON_Y},
		pd->menu.b_start.img->width,
		pd->menu.b_start.img->height))
	{
		pd->menu.button_index = 0;
	}
	else if (within_bounds((t_pos){xpos, ypos},
		(t_pos){CHARS_BUTTON_X,
		CHARS_BUTTON_Y},
		pd->menu.b_chars.img->width,
		pd->menu.b_chars.img->height))
	{
		pd->menu.button_index = 1;
	}
	else if (within_bounds((t_pos){xpos, ypos},
		(t_pos){EXIT_BUTTON_X,
		EXIT_BUTTON_Y},
		pd->menu.b_exit.img->width,
		pd->menu.b_exit.img->height))
	{
		pd->menu.button_index = 2;
	}
	play_sound_if_index_changed(pd);
}

static void	characters_buttons(double xpos, double ypos, t_parsed_data *pd)
{
	if (within_bounds((t_pos){xpos, ypos},
		(t_pos){JESSE_X,
		JESSE_Y},
		pd->chars_menu.b_jesse.img->width,
		pd->chars_menu.b_jesse.img->height))
	{
		pd->chars_menu.button_index = 0;
	}
	else if (within_bounds((t_pos){xpos, ypos},
		(t_pos){CHORUS_X,
		CHORUS_Y},
		pd->chars_menu.b_chorus.img->width,
		pd->chars_menu.b_chorus.img->height))
	{
		pd->chars_menu.button_index = 1;
	}
	else if (within_bounds((t_pos){xpos, ypos},
		(t_pos){OUSSMAC_X,
		OUSSMAC_Y},
		pd->chars_menu.b_oussmac.img->width,
		pd->chars_menu.b_oussmac.img->height))
	{
		pd->chars_menu.button_index = 2;
	}
	play_sound_if_index_changed(pd);
}

static void	button_events(double xpos, double ypos, t_parsed_data *pd)
{
	if (pd->ui_index == 0)
		main_menu_buttons(xpos, ypos, pd);
	else if (pd->ui_index == 1)
		characters_buttons(xpos, ypos, pd);
}

void	handle_mouse_input(double xpos, double ypos, void *param)
{
	t_parsed_data	*pd;

	pd = param;
	button_events(xpos, ypos, pd);
}
