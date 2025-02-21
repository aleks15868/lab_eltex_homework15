#include "graphic.h"

void Name_Writing(WINDOW * win, char *Name){
    char ch;
    int pos =0;
    while (1) {
        ch = wgetch(win); // Считываем символ
        if (ch == 27) {
            Name[pos] = '\0';
            flag_close = 27;
            break;
        } else if (ch == 10) { //нажат Enter
            Name[pos] = '\0';
            if(Name[0]=='\0') flag_close=27;
            break;
        } else if (ch == 127 || ch == 8) {
            if (pos > 0) {
                pos--;
                mvwaddch(win, 1, 1 + pos, ' ');
                wmove(win, 1, 1 + pos);
            }
        } else if (pos < NAME_SIZE - 1) {
            Name[pos] = ch;
            mvwaddch(win, 1, 1 + pos, ch);
            pos++;
        }
        wrefresh(win);
    }
    delwin(win);
}
