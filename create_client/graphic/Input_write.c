#include <stdlib.h>
#include "graphic.h"
void* input_write(void* arg) {
    char input[MESSAGE_SIZE];
    int pos = 0;
    int ch;
    write_name* charaster_name = (write_name*)arg;
    int max_width = charaster_name->max_width_write > MESSAGE_SIZE ? MESSAGE_SIZE : charaster_name->max_width_write;

    while (1) {
        pthread_mutex_lock(&ncurses_mutex); // Блокируем доступ к ncurses
        wrefresh(charaster_name->win); // Обновляем окно
        pthread_mutex_unlock(&ncurses_mutex); // Разблокируем доступ

        ch = wgetch(charaster_name->win); // Считываем символ

        pthread_mutex_lock(&ncurses_mutex); // Блокируем перед изменением окна
        if (ch == 27) {
            input[pos] = '\0';
            flag_close = 27;
            pthread_mutex_unlock(&ncurses_mutex);
            break;
        } else if (ch == '\n') {
            input[ch] = '\0';
            pos = 0;
            input[0] = '\0';
            for (int dx = 0; dx < max_width; dx++) mvwaddch(charaster_name->win, 1, 1 + dx, ' ');
        } else if (ch == 127 || ch == 8) {
            if (pos > 0) {
                pos--;
                mvwaddch(charaster_name->win, 1, 1 + pos, ' ');
                wmove(charaster_name->win, 1, 1 + pos);
            }
        } else if (pos < max_width - 1) {
            input[pos] = ch;
            mvwaddch(charaster_name->win, 1, 1 + pos, ch);
            pos++;
        }
        wrefresh(charaster_name->win);
        pthread_mutex_unlock(&ncurses_mutex); // Разблокируем после обновления окна
    }

    pthread_exit(NULL);
}