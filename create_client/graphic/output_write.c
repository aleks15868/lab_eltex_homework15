#include <stdlib.h>
#include "graphic.h"
void* output_write(void* arg) {
    initscr(); 
    output_message* arguments = (output_message*)arg;
    while (flag_close!=27) 
    {
        mvwprintw(arguments->win_message,10,1,"DDDDD");
        wrefresh(arguments->win_message); // Обновляем окно
    }

    // Выводим введенный текст
    pthread_exit(NULL);
}