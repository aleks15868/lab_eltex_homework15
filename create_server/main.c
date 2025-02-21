#include "server.h"


int main() {
    char flag=0;
    const char *shm_name = SHM_NAME;  // Имя разделяемой памяти

    // Создаем или открываем именованный семафор
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // Создаем разделяемую память
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Устанавливаем размер разделяемой памяти
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Отображаем разделяемую память в адресное пространство процесса
    chat *ptr = (chat *)mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    ptr->cout_people=0;
    ptr->max_message_now=0;
     // Ждем, чтобы другая программа могла прочитать данные
    printf("Data written to shared memory. Press Enter to exit...\n");
    getchar();

    // Убираем отображение памяти
    if (munmap(ptr, SHM_SIZE) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // Закрываем файловый дескриптор
    close(shm_fd);

    // Удаляем разделяемую память
    if (shm_unlink(shm_name) == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }

    // Удаляем семафор (если больше не нужен)
    sem_unlink(SEM_NAME);
    return 0;
}