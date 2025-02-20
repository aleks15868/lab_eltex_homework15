#ifndef _LOGIC_H
#define _LOGIC_H
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
<<<<<<< HEAD
#include <semaphore.h>
=======

>>>>>>> 7940287e0339b2a6f3927c740bf521c0a16ab850

#define MESSAGE_SIZE  40   // Количество символов в сообщении
#define MESSAGE_COUNT 20  // Количество сообщений
#define NAME_SIZE     20  // Количество символов в имени
#define NAME_COUNT    6  // Количество имен

#define SHM_NAME "/my_shm" // Имя разделяемой памяти
<<<<<<< HEAD
#define SEM_NAME "/my_semaphore" // Имя семафора
=======

>>>>>>> 7940287e0339b2a6f3927c740bf521c0a16ab850
typedef struct{
    char cout_people;
    char message_array[MESSAGE_COUNT][NAME_SIZE+MESSAGE_SIZE+1];
    char name_array[NAME_COUNT][NAME_SIZE];
}chat;

#define SHM_SIZE sizeof(chat)  // Размер разделяемой памяти

void open_shared_memory(chat **, int *);
void close_shared_memory(chat **, int *);

#endif