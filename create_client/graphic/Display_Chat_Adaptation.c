// #include "graphic.h"
// #include <ncurses.h>

// void Display_Chat_Adaptation(int *width, int *height){
//     int dx, dy,dlineX,dlineY;
//     for (dx = 0; dx < *width; dx++)
//     {
//         for (dy = 0; dy < *height; dy++)
//         {
//             mvaddch(dy, dx, ' '); 
//         }
//     }
//     for (dlineX = 0; dlineX < *width; dlineX++)
//     {
//        mvaddch(0, dlineX, '-'); 
//     //    mvaddch(*height - 3, dlineX, '-'); 
//        mvaddch(*height - 1, dlineX, '-'); 
//     }
//     for (dlineX = 0; dlineX < *width - NAME_SIZE - 1; dlineX++)
//     {
//        mvaddch(*height - 3, dlineX, '-'); 
//     }
//     for (dlineY = 0; dlineY < *width; dlineY++)
//     {
//        mvaddch(dlineY, 0, '|'); 
//        mvaddch(dlineY, *width - 1, '|'); 
//        mvaddch(dlineY, *width - 2 - NAME_SIZE, '|'); 
//     }
   
//     mvaddch(0, 0, '+');                // Левый верхний угол
//     mvaddch(0, *width - NAME_SIZE - 2, '+');
//     mvaddch(0, *width - 1, '+');        // Правый верхний угол
//     mvaddch(*height - 3, *width - NAME_SIZE - 2, '+');
//     mvaddch(*height - 3, 0, '+');
//     mvaddch(*height - 1, 0, '+');        // Левый нижний угол
//     mvaddch(*height - 1, *width - NAME_SIZE - 2, '+');
//     mvaddch(*height - 1, *width - 1, '+'); // Правый нижний угол
// }