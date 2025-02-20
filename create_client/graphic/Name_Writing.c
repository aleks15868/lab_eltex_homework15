// #include <stdlib.h>
// #include "graphic.h"
// pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

// char Name_Writing(int *width, int *height, char* Name){
//     int flag_close;
//     Write_name name_character;
//     pthread_t thread,thread2;
//     int dx,dy;
//     int mid_height = *height/2;
//     int mid_width = *width/2;
//     char pick = 0;
//     name_character.Name = Name;
//     name_character.mid_height = mid_height;
//     name_character.mid_width = mid_width;
    
//     for (dx = mid_width-DEV_LAYER; dx < mid_width+DEV_LAYER; dx++)
//     {
//         mvaddch(mid_height-2, dx, '-');
//         mvaddch(mid_height, dx, '-');
//     }
//     for (dy = mid_height-2; dy < mid_height; dy++)
//     {
//         mvaddch(dy, mid_width-DEV_LAYER, '|');
//         mvaddch(dy, mid_width+DEV_LAYER, '|');
//     }
//     mvprintw(mid_height-2, mid_width-DEV_LAYER+2, "Name"); 
//     mvaddch(mid_height-2, mid_width-DEV_LAYER, '+');                // Левый верхний угол
//     mvaddch(mid_height-2, mid_width+DEV_LAYER, '+');                // Левый верхний угол
//     mvaddch(mid_height, mid_width-DEV_LAYER, '+'); 
//     mvaddch(mid_height, mid_width+DEV_LAYER, '+'); 
//     mvgetnstr(mid_height-1, mid_width-DEV_LAYER+1, Name, NAME_SIZE);
//     attron(COLOR_PAIR(DARK_GREEN_WHITE_TEXT));
//     if (Name[0]=='\0') {
//         return 1;
//     }
//     else{
//         return pick;
//     }
    
// }
