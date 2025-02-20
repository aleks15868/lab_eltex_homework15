#include <stdio.h>
#include <string.h> 
#include "../graphic/graphic.h"
#include "logic.h"

// Определение глобальной переменной
int flag_close = 0;

// Инициализация мьютекса
pthread_mutex_t ncurses_mutex = PTHREAD_MUTEX_INITIALIZER;

int main(void)
{   int height, width, write_width;
    char flag_close_name;
    // flag_close=0;
    pthread_t thread_input,thread_output;
    int left, right, top, bottom, tlc, trc, blc, brc;

    char left_right_symbol = '|';
    char top_bottom_symbol = '-';
    char input_symbol = '>';
    char side = '+';

    left=right=(int)left_right_symbol;
    top=bottom=(int)top_bottom_symbol;
    tlc=trc=blc=brc=(int)side;
    
    chat *shared_memory_ptr = NULL;  
    int shm_fd; // Файловый дескриптор
    open_shared_memory(&shared_memory_ptr,&shm_fd); //Открытие прослушивания разделяемой памяти
    initscr(); 
    cbreak();             // Отключаем буферизацию строк
    noecho();             // Отключаем отображение вводимых символов
    curs_set(0);          // Скрываем курсор 
    WINDOW *window_message, *window_name, *window_write;
    getmaxyx(stdscr, height, width); // Получение размеров экрана  
    window_message=newwin(height-2, width-NAME_SIZE-2, 0, 0);
    window_name=newwin(height-2, NAME_SIZE+3, 0, width-NAME_SIZE-3);
    window_write=newwin(3, width, height-3, 0);

    char Name[4]={"Danr"};
    wborder(window_message, left, right, top, bottom, tlc, trc, blc, brc);
    wborder(window_name, left, right, top, bottom, tlc, trc, blc, brc);
    wborder(window_write, (int)input_symbol, right, top, bottom, tlc, trc, blc, brc);

    wrefresh(window_message);
    wrefresh(window_name);
    wrefresh(window_write);

    write_name charaster_write={window_write,window_message,width-2,Name,&shared_memory_ptr};
    output_message arguments_for_function = {window_name,window_message,&shared_memory_ptr,
    height-2, width-NAME_SIZE-2
    };
    if (pthread_create(&thread_input, NULL, input_write, (void*)&charaster_write) != 0) {
        perror("Failed to create thread_input");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread_output, NULL, output_write, (void*)&arguments_for_function) != 0) {
        perror("Failed to create thread_output");
        exit(EXIT_FAILURE);
    }
    // Ожидаем завершения потока
    pthread_join(thread_input, NULL);
    pthread_join(thread_output, NULL);
  
    
    endwin();

    close_shared_memory(&shared_memory_ptr,&shm_fd); //закрытие разделяемой памяти
    // printf("\n w:%d, h:%d\n", width,height);
    return 0;
}




// getmaxyx(stdscr, height, width); // Получение размеров экрана  
    // if (pthread_create(&thread_input, NULL, input_write, (void*)Name) != 0) {
    //     perror("pthread_create");
    //     return 1;
    // }
    
    
    // if (pthread_join(thread_input, NULL) != 0) {
    //     perror("pthread_join");
    //     return 1;
    // }