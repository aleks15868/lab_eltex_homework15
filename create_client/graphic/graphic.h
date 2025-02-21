#ifndef _GRAPHIC_H
#define _GRAPHIC_H
#include <ncurses.h>
#include "pthread.h"
#include "../logic/logic.h"

// #define DARK_GREEN 2
// #define WHITE_GREEN 3
// #define DARK_GREEN_WHITE_TEXT 1
// #define WHITE_GREEN_BLACK_TEXT 4
// #define DEV_LAYER 11

// Объявление глобальной переменной
extern int flag_close;
extern int uniq_id;

// Объявление мьютекса для синхронизации доступа к flag_close
extern pthread_mutex_t ncurses_mutex;

typedef struct{
    WINDOW *win;
    WINDOW *win_write;
    int max_width_write;
    char* name;
    chat **ptr;
}write_name;

typedef struct{
    WINDOW *win_name;
    WINDOW *win_message;
    chat **ptr;
    int max_height_write_message;
    int max_width_write_message;
    int max_height_write_name;
    int max_width_write_name;
}output_message;
// char Name_Writing(int *, int *, char* );
// void Display_Chat_Adaptation(int *, int *);
// void *NameWrapper(void *);
void *input_write(void *);
void *output_write(void *);
void Name_Writing(WINDOW *, char*);
#endif