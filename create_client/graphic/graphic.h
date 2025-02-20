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

// Объявление мьютекса для синхронизации доступа к flag_close
extern pthread_mutex_t ncurses_mutex;

typedef struct{
    WINDOW *win;
    int max_width_write;
    char* name;
}write_name;

typedef struct{
    WINDOW *win_name;
    WINDOW *win_message;
    chat **ptr;
}output_message;
// char Name_Writing(int *, int *, char* );
// void Display_Chat_Adaptation(int *, int *);
// void *NameWrapper(void *);
void *input_write(void *);
void *output_write(void *);
void safe_mvwprintw(WINDOW*, int, int, const char*);
void safe_mvwaddch(WINDOW*, int, int, char);
#endif