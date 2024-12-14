#include "loading_animation.h"
#include <pthread.h>
#include <ncurses.h>
#include <unistd.h>

#define DELAY 300000 // Délai de 300ms pour le clignotement

void draw_bulb(int on) {
    if (on) {
        attron(COLOR_PAIR(2)); // Ampoule allumée (jaune)
    } else {
        attron(COLOR_PAIR(1)); // Ampoule éteinte (blanc)
    }

    mvprintw(3, 10, "     ..---..     ");
    mvprintw(4, 10, "    /       \\    ");
    mvprintw(5, 10, "   |         |   ");
    mvprintw(6, 10, "   :         ;   ");
    mvprintw(7, 10, "    \\      //    ");
    mvprintw(8, 10, "     `, Y ,'     ");
    mvprintw(9, 10, "      |_|_|      ");
    mvprintw(10, 10, "     |===|      ");
    mvprintw(11, 10, "     |===|      ");
    mvprintw(12, 10, "     \\_/       ");

    if (on) {
        attroff(COLOR_PAIR(2));
    } else {
        attroff(COLOR_PAIR(1));
    }
}

void draw_loading(int step) {
    attron(COLOR_PAIR(4)); // Texte "Loading..." en vert
    mvprintw(20, 10, "Loading");
    for (int i = 0; i < step % 4; i++) { // Animation des points
        printw(".");
    }
    attroff(COLOR_PAIR(4));
}

int main() {
    initscr();             // Initialisation de ncurses
    noecho();              // Désactiver l'affichage des touches saisies
    curs_set(FALSE);       // Masquer le curseur
    start_color();         // Activer les couleurs
    use_default_colors();  // Permettre l'utilisation des couleurs par défaut

    // Initialisation des paires de couleurs
    init_pair(1, COLOR_WHITE, -1);  // Blanc pour ampoule éteinte
    init_pair(2, COLOR_YELLOW, -1); // Jaune pour ampoule allumée
    init_pair(3, COLOR_CYAN, -1);   // Cyan pour le texte C-WIRE
    init_pair(4, COLOR_GREEN, -1);  // Vert pour le texte "Loading..."

    int on = 0; // État de l'ampoule
    int step = 0;

    while (1) {
        clear();
        draw_bulb(on);
        draw_loading(step);
        refresh();
        usleep(DELAY);

        on = !on;    // Alterner l'état de l'ampoule
        step++;      // Incrémenter le pas pour l'animation
    }

    endwin(); // Fin de ncurses
    return 0;
}