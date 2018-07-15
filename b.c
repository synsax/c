#include <curses.h>

#define WIDTH 300
#define HEIGHT 200

char map[HEIGHT][WIDTH];

void init() {
    int i,j;
    for(i=0;i<HEIGHT;i++) {
        for(j=0;j<WIDTH;j++) {
            map[i][j] = ' ';
        }
    }
}

void draw() {
    int i,j;
    for(i=0;i<HEIGHT;i++) {
        for(j=0;j<WIDTH;j++) {
            mvaddch(i,j,map[i][j]);
        }
    }
}

void setup(char *st[], int len, int x, int y) {
    int i,j;
    for(i=0;i<len;i++) {
        j = 0;
        while(st[i][j] != '\0') {
            if(i+y > HEIGHT || j+x > WIDTH) break;
            map[i+y][j+x] = st[i][j];
        }
    }
}

int main()
{
    WINDOW *win = initscr();
    noecho(); // Deterrence echo back
    cbreak(); // Deterrence buffuring
    keypad(win, TRUE); // Use cursor keys
    
    init();
    
    char *st[] = {
        "######################",
        "#                    #",
        "#          #         #",
        "#          #         #",
        "#    $     #         #",
        "#          #         #",
        "#          #         #",
        "######################",
    };
    int stn = sizeof(st)/sizeof(st[0]);
    //setup(st, stn, 0, 0);
    
    int x = 10, y = 10;
    draw();
    mvaddch(y,x,'@');

    while(1) {
        int dx = 0,dy = 0;
        int ch = wgetch(win);
        
        switch(ch) {
            case KEY_UP: {
                dx = 0; dy = -1;
                break;
            }
            case KEY_DOWN: {
                dx = 0; dy = 1;
                break;
            }
            case KEY_LEFT: {
                dx = -1; dy = 0;
                break;
            }
            case KEY_RIGHT: {
                dx = 1; dy = 0;
                break;
            }
        }
        draw();
        mvaddch(y, x, ' ');
        x += dx; y += dy;
        //mvaddch(0,0,(char)inch());
        mvaddch(y, x, '@');
    }
    endwin();
    return 0;
}
