#include "logic.h"

void open_shared_memory(chat **ptr, int *shm_fd){
    const char *shm_name = SHM_NAME; 
    // Открываем разделяемую память
    *shm_fd = shm_open(shm_name, O_RDONLY, 0666);
    if (*shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    printf("\nOpen   %d\n", *shm_fd);
    // Отображаем разделяемую память в адресное пространство процесса
    *ptr = (chat *)mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, *shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
}

void close_shared_memory(chat **ptr, int *shm_fd){
    printf("\nClose   %d\n", *shm_fd);
     // Убираем отображение памяти
    if (munmap(*ptr, SHM_SIZE) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // Закрываем файловый дескриптор
    close(*shm_fd);
}