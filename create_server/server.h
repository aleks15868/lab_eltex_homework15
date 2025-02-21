#ifndef _SERVER_H
#define _SERVER_H
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#define NAME_SIZE 20

#define MESSAGE_SIZE  40   // Количество символов в сообщении
#define MESSAGE_COUNT 5  // Количество сообщений
#define NAME_SIZE     20  // Количество символов в имени
#define NAME_COUNT    6  // Количество имен

#define SHM_NAME "/my_shm" // Имя разделяемой памяти
#define SEM_NAME "/my_semaphore" // Имя семафора

typedef struct{
    int id;
    char name[NAME_SIZE];
}name_un;

typedef struct{
    char cout_people;
    char max_message_now;
    char message_array[MESSAGE_COUNT][NAME_SIZE+MESSAGE_SIZE+2];
    name_un name_array[NAME_COUNT];
}chat;



#define SHM_SIZE sizeof(chat)  // Размер разделяемой памяти


#endif