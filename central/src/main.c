#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *choices[] = {
	"Lampada 01 (Cozinha)",
	"Lampada 02 (Sala)",
	"Lampada 03 (Quarto 01)",
	"Lampada 04 (Quarto 02)",
	"Ar-Condicionado 01 (Quarto 01)",
	"Ar-Condicionado 02 (Quarto 02)",
	"Alarme",
	(char *)NULL,
};

ITEM **my_items;
int c;
MENU *my_menu;
WINDOW *my_menu_win;
WINDOW *my_menu_win_info;
int n_choices, i;
ITEM *cur_item;

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{
	int length, x, y;
	float temp;

	if (win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if (startx != 0)
		x = startx;
	if (starty != 0)
		y = starty;
	if (width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length) / 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

void render_input_menu()
{
	/* Create items */
	n_choices = ARRAY_SIZE(choices);
	my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
	for (i = 0; i < n_choices; ++i)
		my_items[i] = new_item(choices[i], "");

	/* Crate menu */
	my_menu = new_menu((ITEM **)my_items);

	/* Make the menu multi valued */
	menu_opts_off(my_menu, O_ONEVALUE);

	/* Create the window to be associated with the menu */
	my_menu_win = newwin(15, 40, 0, 0);
	keypad(my_menu_win, TRUE);

	/* Set main window and sub window */
	set_menu_win(my_menu, my_menu_win);
	set_menu_sub(my_menu, derwin(my_menu_win, 7, 38, 3, 1));

	/* Set fore ground and back ground of the menu */
	set_menu_fore(my_menu, COLOR_PAIR(2) | A_REVERSE);
	set_menu_back(my_menu, COLOR_PAIR(1));

	/* Set menu mark to the string " * " */
	set_menu_mark(my_menu, " -> ");

	box(my_menu_win, 0, 0);

	print_in_middle(my_menu_win, 1, 0, 40, "Interruptores", COLOR_PAIR(3));

	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
	mvwaddch(my_menu_win, 2, 39, ACS_RTEE);

	post_menu(my_menu);
	wrefresh(my_menu_win);
}

void render_info_win()
{
	char *sensors[] = {
		"Sensor de Presença 01 (Sala)",
		"Sensor de Presença 02 (Cozinha)  ",
		"Sensor Abertura 01 (Porta Cozinha)",
		"Sensor Abertura 02 (Janela Cozinha)",
		"Sensor Abertura 03 (Porta Sala)",
		"Sensor Abertura 04 (Janela Sala)",
		"Sensor Abertura 05 (Janela Quarto 01)",
		"Sensor Abertura 06 (Janela Quarto 02)"
	};

	my_menu_win_info = newwin(15, 45, 0, 40);
	keypad(my_menu_win_info, TRUE);

	box(my_menu_win_info, 0, 0);

	print_in_middle(my_menu_win_info, 1, 0, 40, "Sensores", COLOR_PAIR(3));

	mvwaddch(my_menu_win_info, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win_info, 2, 1, ACS_HLINE, 43);
	mvwaddch(my_menu_win_info, 2, 44, ACS_RTEE);

	for (int i = 0; i < ARRAY_SIZE(sensors); i++)
	{
		mvwprintw(my_menu_win_info, i + 3, 2, sensors[i]);
	}

	mvwprintw(my_menu_win_info, ARRAY_SIZE(sensors) + 4, 2, "Temperatura: %4.2f \tHumidade: %4.2f", 10, 10);

	wrefresh(my_menu_win_info);
}

int main()
{

	/* Initialize curses */
	initscr();
	start_color();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);

	render_info_win();
	render_input_menu();

	mvprintw(LINES - 3, 0, "Use <SPACE> para acionar o dispositivo");
	mvprintw(LINES - 2, 0, "<ENTER> to see presently selected items(F1 to Exit)");
	refresh();

	while ((c = wgetch(my_menu_win)) != KEY_F(1))
	{
		switch (c)
		{
		case KEY_DOWN:
			menu_driver(my_menu, REQ_DOWN_ITEM);
			break;
		case KEY_UP:
			menu_driver(my_menu, REQ_UP_ITEM);
			break;
		case ' ':
			menu_driver(my_menu, REQ_TOGGLE_ITEM);
			break;
		case 10: /* Enter */
		{
			char temp[200];
			ITEM **items;

			items = menu_items(my_menu);
			temp[0] = '\0';
			for (i = 0; i < item_count(my_menu); ++i)
				if (item_value(items[i]) == TRUE)
				{
					strcat(temp, item_name(items[i]));
					strcat(temp, " ");
				}
			move(20, 0);
			clrtoeol();
			mvprintw(20, 0, temp);
			refresh();
		}
		break;
		}
		wrefresh(my_menu_win);
	}

	/* Unpost and free all the memory taken up */
	unpost_menu(my_menu);
	free_menu(my_menu);
	for (i = 0; i < n_choices; ++i)
		free_item(my_items[i]);
	endwin();
}