#ifndef _SERVER_H
#define _SERVER_H
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#define NAME_SIZE 20

#define MESSAGE_SIZE  40   // Количество символов в сообщении
#define MESSAGE_COUNT 20  // Количество сообщений
#define NAME_SIZE     20  // Количество символов в имени
#define NAME_COUNT    6  // Количество имен

#define SHM_NAME "/my_shm" // Имя разделяемой памяти

typedef struct{
    char cout_people;
    char message_array[MESSAGE_COUNT][MESSAGE_SIZE];
    char name_array[NAME_COUNT][NAME_SIZE];
}chat;

#define SHM_SIZE sizeof(chat)  // Размер разделяемой памяти


#endif