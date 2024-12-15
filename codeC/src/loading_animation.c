#include "loading_animation.h"
#include <pthread.h>
#include <ncurses.h>
#include <unistd.h>

#define DELAY 300000 // 300ms delay for flashing

void draw_bulb(int on) {
    if (on) {
        attron(COLOR_PAIR(2)); // Bulb on (yellow)
    } else {
        attron(COLOR_PAIR(1)); // Bulb off (white)
    }

    mvprintw(3, 10, "     ..---..     ");
    mvprintw(4, 10, "    /       \\    ");
    mvprintw(5, 10, "   |         |   ");
    mvprintw(6, 10, "   :         ;   ");
    mvprintw(7, 10, "    \\      //    ");
    mvprintw(8, 10, "     `, Y ,'     ");
    mvprintw(9, 10, "      |_|_|      ");
    mvprintw(10, 10, "      |===|      ");
    mvprintw(11, 10, "      |===|      ");
    mvprintw(12, 10, "       \\_/       ");
    
    if (on) {
        attroff(COLOR_PAIR(2));
    } else {
        attroff(COLOR_PAIR(1));
    }
}

void draw_loading(int step) {
    attron(COLOR_PAIR(4)); // Text "Loading..." in green
    mvprintw(20, 10, "Loading");
    for (int i = 0; i < step % 4; i++) { // Animation of points
        printw(".");
    }
    attroff(COLOR_PAIR(4));
}

int main() {
    initscr();             // Initialization of ncurses
    noecho();              // Disable the display of keystrokes
    curs_set(FALSE);       // Hide the mouse
    start_color();         // Enable the colors
    use_default_colors();  // Allow the use of default colors

    // Initialization of color pairs
    init_pair(1, COLOR_WHITE, -1);  // White for bulb off
    init_pair(2, COLOR_YELLOW, -1); // Yellow for light bulb
    init_pair(3, COLOR_CYAN, -1);   // Cyan for C-WIRE text
    init_pair(4, COLOR_GREEN, -1);  // Green for the text "Loading..."

    int on = 0; // Bulb condition
    int step = 0;

    while (1) {
        clear();
        draw_bulb(on);
        draw_loading(step);
        refresh();
        usleep(DELAY);

        on = !on;    // Alternate bulb state
        step++;      // Increment the step for animation
    }

    endwin(); // End of ncurses
    return 0;
}