#include <stdlib.h>
#include "graphic.h"
void* output_write(void* arg) {
    int line,size,index_y,max_index_x,reverse_insex_y,сheck_for_zero_size,max_now_height;
    size_t index_x;
    int start,exd,cout_message,dx,dy,cout_name;
    output_message* arguments = (output_message*)arg;
    int max_size_message = arguments->max_width_write_message-2;
    chat *shared_memory_ptr = *arguments->ptr;
    char *output = (char *)malloc((max_size_message+1) * sizeof(int));
    if (output == NULL) {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    // output[max_size_message]='\0';
    while (flag_close != 27) 
    {
        sleep(0.5);
        pthread_mutex_lock(&ncurses_mutex); // Блокируем доступ к ncurses
        // wclear(arguments->win_message);
        for (dy = 1; dy < arguments->max_height_write_message-1; dy++)
        {
            for (dx = 1; dx < max_size_message+1; dx++)
            {
                mvwaddch(arguments->win_message, dy, dx, ' ');
            }
        }

        for (dy = 1; dy < arguments->max_height_write_name-1; dy++)
        {
            mvwaddch(arguments->win_name, dy, 0, '|');
            for (dx = 1; dx < arguments->max_width_write_name-1; dx++)
            {
                mvwaddch(arguments->win_name, dy, dx, ' ');
            }
        }

        max_now_height=arguments->max_height_write_message-1;
        for (cout_name = 0; cout_name < shared_memory_ptr->cout_people; cout_name++)
        {
            if (shared_memory_ptr->name_array[cout_name].id!=uniq_id)
            {
                mvwprintw(arguments->win_name, 2+cout_name, 0, "|%s",
                shared_memory_ptr->name_array[cout_name].name);
            }
            else{
                mvwprintw(arguments->win_name, 2+cout_name, 0, ">%s",
                shared_memory_ptr->name_array[cout_name].name);
            }
        }
        mvwprintw(arguments->win_name, 1, 1, "Con:%d/%d",shared_memory_ptr->cout_people,NAME_COUNT);
        for (cout_message = 0; cout_message < shared_memory_ptr->max_message_now; cout_message++)
        {
            size = strlen(shared_memory_ptr->message_array[cout_message]);
            сheck_for_zero_size = size%max_size_message!=0 ? size/max_size_message : size/max_size_message-1;
            for (index_y = сheck_for_zero_size; index_y >= 0; index_y--)
            {
                if(max_now_height>=2){
                reverse_insex_y=сheck_for_zero_size-index_y;
                max_now_height--;
                
                max_index_x = index_y*max_size_message+max_size_message>size ? 
                size : index_y*max_size_message+max_size_message;
                for (index_x = index_y*max_size_message; index_x < max_index_x; index_x++)
                {
                    output[index_x-(index_y*max_size_message)]=shared_memory_ptr->message_array[cout_message][index_x];
                }
                output[index_x-(index_y*max_size_message)]='\0';
                mvwprintw(arguments->win_message, max_now_height, 1, "%s",output);
                }
                else{
                    break;
                }
                
            }
        }
        // wclear(arguments->win_message);
        wrefresh(arguments->win_message); // Обновляем окно
        wrefresh(arguments->win_name); 
        pthread_mutex_unlock(&ncurses_mutex); // Разблокируем доступ
    }
    free(output);
    pthread_exit(NULL);
}