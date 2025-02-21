#include <stdio.h>
#include <string.h> 
#include "../graphic/graphic.h"
#include "logic.h"

// Определение глобальной переменной
int flag_close = 0;
int uniq_id;
// Инициализация мьютекса
pthread_mutex_t ncurses_mutex = PTHREAD_MUTEX_INITIALIZER;

int main(void)
{   
    chat *shared_memory_ptr = NULL;  
    int shm_fd; // Файловый дескриптор
    open_shared_memory(&shared_memory_ptr,&shm_fd); //Открытие прослушивания разделяемой памяти
    if(shared_memory_ptr->cout_people+1>NAME_COUNT){
        perror("There are too many people in the lobby");
        exit(EXIT_FAILURE);
    }
    int height, width, write_width;
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
    uniq_id=generate_unique_id();

    initscr(); 
    cbreak();             // Отключаем буферизацию строк
    noecho();             // Отключаем отображение вводимых символов
    curs_set(0);          // Скрываем курсор 
    WINDOW *window_message, *window_name, *window_write, *window_name_input;
    getmaxyx(stdscr, height, width); // Получение размеров экрана  
    window_message=newwin(height-2, width-NAME_SIZE-2, 0, 0);
    window_name=newwin(height-2, NAME_SIZE+3, 0, width-NAME_SIZE-3);
    window_write=newwin(3, width, height-3, 0);
    window_name_input=newwin(3, NAME_SIZE+1, (height-3)/2, (width-NAME_SIZE+1)/2);

    char Name[NAME_SIZE];
    wborder(window_message, left, right, top, bottom, tlc, trc, blc, brc);
    wborder(window_name, left, right, top, bottom, tlc, trc, blc, brc);
    wborder(window_write, (int)input_symbol, right, top, bottom, tlc, trc, blc, brc);
    wborder(window_name_input, left, right, top, bottom, tlc, trc, blc, brc);
    mvwprintw(window_name_input, 0, 2, "Name:");
    mvwprintw(window_name, 1, 1, "Con:%d/%d",shared_memory_ptr->cout_people,NAME_COUNT);
    
    wrefresh(window_message);
    wrefresh(window_name);
    wrefresh(window_write);
    wrefresh(window_name_input);

    Name_Writing(window_name_input, Name);
    wborder(window_message, left, right, top, bottom, tlc, trc, blc, brc);
    wborder(window_name, left, right, top, bottom, tlc, trc, blc, brc);
    wborder(window_write, (int)input_symbol, right, top, bottom, tlc, trc, blc, brc);
    wrefresh(window_message);
    wrefresh(window_name);
    wrefresh(window_write);
    //Name<-end
    write_name charaster_write={window_write,window_message,width-2,Name,&shared_memory_ptr};
    output_message arguments_for_function = {window_name,window_message,&shared_memory_ptr,
    height-2, width-NAME_SIZE-2,height-2, NAME_SIZE+3};
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
    // printf("\n Id:%d", uniq_id);
    return 0;
}