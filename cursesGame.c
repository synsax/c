/*
    cc *.c -lcurses
*/
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#define WIDTH 300
#define HEIGHT 200

char map[HEIGHT][WIDTH];

typedef struct {
    int x, y;
    char c;
    int isGetted;
}enemy;

void setEnemy(enemy *e, const char c, int x, int y) {
    e->c = c;
    e->x = x;
    e->y = y;
    e->isGetted = 0;
    map[y][x] = c;
}

void mvEnemy(enemy *e) {
    int dx = rand()%2 ? rand()%2 : (rand()%2)*-1;
    int dy = rand()%2 ? rand()%2 : (rand()%2)*-1;
    if(e->isGetted) {
        map[e->y][e->x] = '$';
        e->isGetted = 0;
    }
    else {
        map[e->y][e->x] = ' ';
    }
    e->x += dx;
    e->y += dy;
    if(map[e->y][e->x] == '#') {
        e->x -= dx;
        e->y -= dy;
    }
    if(map[e->y][e->x] == '$') {
        e->isGetted = 1;
    }
    map[e->y][e->x] = e->c;
}

void initMap() {
    int i,j;
    for(i=0;i<HEIGHT;i++) {
        for(j=0;j<WIDTH;j++) {
            printw("%c",map[i][j]);
            map[i][j] = ' ';
        }
    }
}

void draw() {
    erase();
    int i,j;
    for(i=0;i<HEIGHT;i++) {
        for(j=0;j<WIDTH;j++) {
            if(map[i][j] == ' ') continue;
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
            j++;
        }
    }
}

int main()
{
    WINDOW *win = initscr();
    noecho(); // Deterrence echo back
    cbreak(); // Deterrence buffuring
    keypad(win, TRUE); // Use cursor keys

RESTART:

    srand((unsigned)time(NULL));

    int score = 0;
    int isEnded = 0;
    int isCleared = 0;

    initMap();
    
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
    setup(st, stn, 5, 5);

    enemy e;
    setEnemy(&e,'<',10,7);

    int x = 20, y = 10;
    draw();

    move(1,1);
    printw("Score : %d",score);

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
        x += dx; y += dy;
        mvEnemy(&e);
        if(map[y][x] == '#') {
            x-=dx; y-=dy;
        }
        if(map[y][x] == '$') {
            score++;
            map[y][x] = ' ';
            int _x = score%2 ? 11 : -11;
            map[y][x+_x] = '$';
        }
        if(map[y][x] == e.c) {
            isEnded = 1;
            break;
        }
        draw();
        move(1,1);
        printw("Score : %d",score);
        mvaddch(y, x, '@');
    }

    if(isEnded) {
        clear();
        move(13,43);
        printw("Score : %d", score);
        move(15,43);
        printw("Game Over");
        move(18,40);
        printw("[r]estart [e]nd");
    }
    while(isEnded) {
        int i = wgetch(win);
        if(i == 'e') break;
        else if(i == 'r') {
            clear();
            goto RESTART;
        }
    }
    endwin();
    return 0;
}
