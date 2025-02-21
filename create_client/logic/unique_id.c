#include "logic.h"

int generate_unique_id() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    // Комбинируем секунды и микросекунды
    int unique_id = (int)((tv.tv_usec) & 0xFFFFFFFF);

    return unique_id;
}