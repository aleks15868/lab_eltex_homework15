#include <stdlib.h>
#include "graphic.h"
void* input_write(void* arg) {
    char input[MESSAGE_SIZE];
    int pos = 0;
    int ch;
    write_name* charaster_name = (write_name*)arg;
    int max_width = charaster_name->max_width_write > MESSAGE_SIZE ? MESSAGE_SIZE : charaster_name->max_width_write;

    // Создаем или открываем именованный семафор
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    
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
        } else if (ch == 10) { //нажат Enter
            input[ch] = '\0';
            // Пытаемся захватить семафор
            mvwprintw(charaster_name->win_write, 1, 1,"Process %d is trying to acquire the semaphore...\n", getpid());
            if (sem_wait(sem) == -1) {
                perror("sem_wait");
                pthread_mutex_unlock(&ncurses_mutex);
                sem_close(sem);
                exit(EXIT_FAILURE);
            }

            // Критическая секция
            mvwprintw(charaster_name->win_write, 2, 1,"Process %d has entered the critical section.\n", getpid());
            mvwprintw(charaster_name->win_write, 3, 1,"Process %d is leaving the critical section.\n", getpid());

            // Освобождаем семафор
            if (sem_post(sem) == -1) {
                perror("sem_post");
                pthread_mutex_unlock(&ncurses_mutex);
                sem_close(sem);
                exit(EXIT_FAILURE);
            }

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

    // Закрываем семафор
    sem_close(sem);

    pthread_exit(NULL);
}