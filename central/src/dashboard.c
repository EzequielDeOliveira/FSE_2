#include <menu.h>
#include "data.h"
#include "server.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *choices[] = {
    "0 Lampada 01 (Cozinha)",
    "1 Lampada 02 (Sala)",
    "2 Lampada 03 (Quarto 01)",
    "3 Lampada 04 (Quarto 02)",
    "4 Ar-Condicionado 01 (Quarto 01)",
    "5 Ar-Condicionado 02 (Quarto 02)",
    "6 Alarme",
    (char *)NULL,
};

char *sensors[] = {
    "Sensor de Presença 01 (Sala)",
    "Sensor de Presença 02 (Cozinha)  ",
    "Sensor Abertura 01 (Porta Cozinha)",
    "Sensor Abertura 02 (Janela Cozinha)",
    "Sensor Abertura 03 (Porta Sala)",
    "Sensor Abertura 04 (Janela Sala)",
    "Sensor Abertura 05 (Janela Quarto 01)",
    "Sensor Abertura 06 (Janela Quarto 02)"};

ITEM **my_items;
ITEM *cur_item;
MENU *my_menu;
WINDOW *my_menu_win;
WINDOW *my_menu_win_info;
int c;
int n_choices, i;

int device_status(int choice)
{
    Data data = get_data();

    if (choices[choice] == 0)
    {
        return data.lamp1;
    }
    else if (choices[choice] == 1)
    {
        return data.lamp2;
    }
    else if (choices[choice] == 2)
    {
        return data.lamp3;
    }
    else if (choices[choice] == 3)
    {
        return data.lamp4;
    }
    else if (choices[choice] == 4)
    {
        return data.air1;
    }
    else if (choices[choice] == 5)
    {
        return data.air2;
    }
    else if (choices[choice] == 6)
    {
        return data.alarm;
    }
}

void change_device_status(ITEM *item)
{
    Data data = get_data();

    char *name = strdup(item_name(item));

    if (strcmp(item_name(item), choices[0]) == 0)
    {
        send_command(LAMP_1);
        if (data.lamp1 == 1)
        {
            item->description.str = "OFF";
            data.lamp1 = 0;
        }
        else
        {
            item->description.str = " ON";
            data.lamp1 = 1;
        }
    }
    else if (strcmp(item_name(item), choices[1]) == 0)
    {
        send_command(LAMP_2);
        if (data.lamp2 == 1)
        {
            item->description.str = "OFF";
            data.lamp2 = 0;
        }
        else
        {
            item->description.str = " ON";
            data.lamp2 = 1;
        }
    }
    else if (strcmp(item_name(item), choices[2]) == 0)
    {
        send_command(LAMP_3);
        if (data.lamp3 == 1)
        {
            item->description.str = "OFF";
            data.lamp3 = 0;
        }
        else
        {
            item->description.str = " ON";
            data.lamp3 = 1;
        }
    }
    else if (strcmp(item_name(item), choices[3]) == 0)
    {
        send_command(LAMP_4);
        if (data.lamp4 == 1)
        {
            item->description.str = "OFF";
            data.lamp4 = 0;
        }
        else
        {
            item->description.str = " ON";
            data.lamp4 = 1;
        }
    }
    else if (strcmp(item_name(item), choices[4]) == 0)
    {
        send_command(AIR_1);
        if (data.air1 == 1)
        {
            item->description.str = "OFF";
            data.air1 = 0;
        }
        else
        {
            item->description.str = " ON";
            data.air1 = 1;
        }
    }
    else if (strcmp(item_name(item), choices[5]) == 0)
    {
        send_command(AIR_2);
        if (data.air2 == 1)
        {
            item->description.str = "OFF";
            data.air2 = 0;
        }
        else
        {
            item->description.str = " ON";
            data.air2 = 1;
        }
    }
    else if (strcmp(item_name(item), choices[6]) == 0)
    {
        if (data.alarm == 1)
        {
            item->description.str = "OFF";
            data.alarm = 0;
        }
        else
        {
            item->description.str = " ON";
            data.alarm = 1;
        }
    }

    set_data(data);
    menu_driver(my_menu, REQ_TOGGLE_ITEM);
    refresh();
}

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
    {
        my_items[i] = new_item(choices[i], device_status(i) == 1 ? "ON" : "OFF");
    }

    /* Crate menu */
    my_menu = new_menu((ITEM **)my_items);

    /* Make the menu multi valued */
    menu_opts_off(my_menu, O_ONEVALUE);

    my_menu_win = newwin(15, 50, 0, 0);
    keypad(my_menu_win, TRUE);

    /* Set main window and sub window */
    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win, 7, 40, 3, 2));

    /* Set fore ground and back ground of the menu */
    set_menu_fore(my_menu, COLOR_PAIR(2) | A_REVERSE);
    set_menu_back(my_menu, COLOR_PAIR(1));

    /* Set menu mark to the string " * " */
    set_menu_mark(my_menu, " -> ");

    box(my_menu_win, 0, 0);

    print_in_middle(my_menu_win, 1, 0, 40, "Interruptores", COLOR_PAIR(3));

    mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
    mvwhline(my_menu_win, 2, 1, ACS_HLINE, 49);
    mvwaddch(my_menu_win, 2, 49, ACS_RTEE);

    post_menu(my_menu);
    wrefresh(my_menu_win);
}

void render_info_win(float temperature, float humidity)
{
    my_menu_win_info = newwin(15, 51, 0, 50);
    keypad(my_menu_win_info, TRUE);

    box(my_menu_win_info, 0, 0);

    print_in_middle(my_menu_win_info, 1, 0, 50, "Sensores", COLOR_PAIR(3));

    mvwaddch(my_menu_win_info, 2, 0, ACS_LTEE);
    mvwhline(my_menu_win_info, 2, 1, ACS_HLINE, 50);
    mvwaddch(my_menu_win_info, 2, 50, ACS_RTEE);

    for (int i = 0; i < ARRAY_SIZE(sensors); i++)
    {
        mvwprintw(my_menu_win_info, i + 3, 2, sensors[i]);
    }

    mvwprintw(my_menu_win_info, ARRAY_SIZE(sensors) + 4, 2, "Temperatura: %4.2f \tHumidade: %4.2f", temperature, humidity);

    wrefresh(my_menu_win_info);
}

int dashboard()
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

    render_info_win(0,0);
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
            change_device_status(current_item(my_menu));
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