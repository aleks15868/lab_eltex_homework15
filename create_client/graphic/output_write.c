#include <stdlib.h>
#include "graphic.h"
void* output_write(void* arg) {
    initscr(); 
    output_message* arguments = (output_message*)arg;
    while (flag_close != 27) {
        pthread_mutex_lock(&ncurses_mutex); // Блокируем доступ к ncurses
        mvwprintw(arguments->win_message, 10, 1, "DDDDD");
        wrefresh(arguments->win_message); // Обновляем окно
        pthread_mutex_unlock(&ncurses_mutex); // Разблокируем доступ
    }
    pthread_exit(NULL);
}