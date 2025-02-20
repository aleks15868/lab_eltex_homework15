#include "logic.h"

void open_shared_memory(chat **ptr, int *shm_fd){
    const char *shm_name = SHM_NAME; 
    // Открываем разделяемую память
    *shm_fd = shm_open(shm_name, O_RDWR, 0666);
    if (*shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    // Отображаем разделяемую память в адресное пространство процесса
    *ptr = (chat *)mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, *shm_fd, 0);
    if (*ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
}

void close_shared_memory(chat **ptr, int *shm_fd){
     // Убираем отображение памяти
    if (munmap(*ptr, SHM_SIZE) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // Закрываем файловый дескриптор
    close(*shm_fd);
}