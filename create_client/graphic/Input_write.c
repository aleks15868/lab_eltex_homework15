#include <stdlib.h>
#include "graphic.h"
void* input_write(void* arg) {
    char input[MESSAGE_SIZE];
    char message_input[NAME_SIZE+MESSAGE_SIZE+2];
    int pos = 0;
    int ch, index_message;
    int cout_people;
    write_name* charaster_name = (write_name*)arg;
    int max_width = charaster_name->max_width_write > MESSAGE_SIZE ? MESSAGE_SIZE : charaster_name->max_width_write;
    chat *shared_memory_ptr = *charaster_name->ptr;
    // Создаем или открываем именованный семафор
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    pthread_mutex_lock(&ncurses_mutex); // Блокируем доступ к ncurses
    // Пытаемся захватить семафор
    if (sem_wait(sem) == -1) {
        perror("sem_wait");
        pthread_mutex_unlock(&ncurses_mutex);
        sem_close(sem);
        exit(EXIT_FAILURE);
    }
    cout_people=shared_memory_ptr->cout_people++;
    shared_memory_ptr->name_array[cout_people].id=uniq_id;
    strncpy(shared_memory_ptr->name_array[cout_people].name,charaster_name->name, (NAME_SIZE)-1); 
    // Освобождаем семафор
    if (sem_post(sem) == -1) {
        perror("sem_post");
        pthread_mutex_unlock(&ncurses_mutex);// Разблокируем доступ к ncurses
        sem_close(sem);
        exit(EXIT_FAILURE);
    }
    pthread_mutex_unlock(&ncurses_mutex); // Разблокируем доступ к ncurses

    while (flag_close!=27) {
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
            input[pos] = '\0';
            // Пытаемся захватить семафор
            snprintf(message_input, sizeof(message_input), "%s>:%s", charaster_name->name, input);
            if (sem_wait(sem) == -1) {
                perror("sem_wait");
                pthread_mutex_unlock(&ncurses_mutex);
                sem_close(sem);
                exit(EXIT_FAILURE);
            }
            for (index_message = MESSAGE_COUNT-1; index_message > 0; index_message--)
            {
                //переносим элемент на один вперед [0]=>[1]
                strncpy(shared_memory_ptr->message_array[index_message], 
                shared_memory_ptr->message_array[index_message-1], (NAME_SIZE+MESSAGE_SIZE+1)-1); 
            }
            strncpy(shared_memory_ptr->message_array[0], message_input, (NAME_SIZE+MESSAGE_SIZE+1)-1); //копируем ввод с клавиатуры в первый элемент массива
            // Освобождаем семафор
            if (sem_post(sem) == -1) {
                perror("sem_post");
                pthread_mutex_unlock(&ncurses_mutex);
                sem_close(sem);
                exit(EXIT_FAILURE);
            }
            if (shared_memory_ptr->max_message_now>=MESSAGE_COUNT)
            {
                shared_memory_ptr->max_message_now=MESSAGE_COUNT;
            }
            else
            {
                shared_memory_ptr->max_message_now++;
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

    pthread_mutex_lock(&ncurses_mutex); // Блокируем доступ к ncurses
    // Пытаемся захватить семафор
    if (sem_wait(sem) == -1) {
        perror("sem_wait");
        pthread_mutex_unlock(&ncurses_mutex);
        sem_close(sem);
        exit(EXIT_FAILURE);
    }
    for (int cout_i = 0; cout_i < shared_memory_ptr->cout_people; cout_i++)
    {
        if (shared_memory_ptr->name_array[cout_i].id == uniq_id)
        {
            // Сдвигаем все элементы после удаляемого влево
            for (int cout_i_temp = cout_i; cout_i_temp < shared_memory_ptr->cout_people - 1; cout_i_temp++)
            {
                shared_memory_ptr->name_array[cout_i_temp] = shared_memory_ptr->name_array[cout_i_temp + 1];
            }

            // Уменьшаем количество элементов в массиве
            shared_memory_ptr->cout_people--;

            // Выходим из цикла, так как элемент уже удален
            break;
        }
    }
    // shared_memory_ptr->cout_people = shared_memory_ptr->cout_people>0 ? 
    // shared_memory_ptr->cout_people-- : 0;
    // Освобождаем семафор
    if (sem_post(sem) == -1) {
        perror("sem_post");
        pthread_mutex_unlock(&ncurses_mutex);// Разблокируем доступ к ncurses
        sem_close(sem);
        exit(EXIT_FAILURE);
    }
    pthread_mutex_unlock(&ncurses_mutex); // Разблокируем доступ к ncurses
    // Закрываем семафор
    sem_close(sem);

    pthread_exit(NULL);
}