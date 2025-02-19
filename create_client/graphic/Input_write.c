#include <stdlib.h>
#include "graphic.h"
void* input_write(void* arg) {
    char input[MESSAGE_SIZE];
    int pos = 0;
    int ch;
    write_name* charaster_name = (write_name*)arg;
    int max_width = charaster_name->max_width_write > MESSAGE_SIZE ? MESSAGE_SIZE : charaster_name->max_width_write;
    // Вводим текст
    while (1) {
        wrefresh(charaster_name->win); // Обновляем окно
        ch = wgetch(charaster_name->win); // Считываем символ

        if (ch == 27) { // Если нажата клавиша ESC
            input[pos] = '\0'; // Завершаем строку
            flag_close = 27;
            break;
        } else if (ch == '\n') { // Если нажата клавиша Enter
            input[ch] = '\0'; // Завершаем строку
            pos = 0;
            input[0] = '\0';
            for (int dx = 0; dx < max_width; dx++) mvwaddch(charaster_name->win, 1, 1 + dx, ' ');
            // break;
        } else if (ch == 127 || ch == 8) { // Если нажата клавиша Backspace
            if (pos > 0) {
                pos--;
                mvwaddch(charaster_name->win, 1, 1 + pos, ' '); // Удаляем символ с экрана
                wmove(charaster_name->win, 1, 1 + pos); // Возвращаем курсор на место

            }
        } else if (pos < max_width - 1) { // Если есть место в буфере
            input[pos] = ch; // Сохраняем символ
            mvwaddch(charaster_name->win, 1, 1 + pos, ch); // Выводим символ на экран
            pos++;
        }

    }

    // Выводим введенный текст
    wrefresh(charaster_name->win);
    pthread_exit(NULL);
}