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
}enemy;

char judge(int x, int y);

void setEnemy(enemy *e, const char c, int x, int y) {
    e->c = c;
    e->x = x;
    e->y = y;
    map[y][x] = c;
}

void mvEnemy(enemy *e) {
    int dx = rand()%2 ? rand()%2 : (rand()%2)*-1;
    int dy = rand()%2 ? rand()%2 : (rand()%2)*-1;
    map[e->y][e->x] = ' ';
    mvaddch(e->y,e->x,' ');
    e->x += dx;
    e->y += dy;
    if(judge(e->x,e->y) == '#') {
        e->x -= dx;
        e->y -= dy;
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

char judge(int x, int y) {
    char m = map[y][x];
    if(m == '#') {
        return '#';
    }
    if(m == '$') {
        return '$';
    }
    if(m == '<') {
        return '<';
    }

    return 0;
}

int main()
{
    WINDOW *win = initscr();
    noecho(); // Deterrence echo back
    cbreak(); // Deterrence buffuring
    keypad(win, TRUE); // Use cursor keys

    srand((unsigned)time(NULL));

    int isEnded = 0;

    int score = 0;
    move(1,1);
    printw("Score : %d",score);
    
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
        mvaddch(y, x, ' ');
        mvEnemy(&e);
        x += dx; y += dy;
        if(judge(x,y) == '#') {
            x-=dx; y-=dy;
        }
        if(judge(x,y) == '$') {
            score++;
            map[y][x] = ' ';
        }
        if(judge(x,y) == e.c) {
            isEnded = 1;
            break;
        }
        draw();
        move(1,1);
        printw("Score : %d",score);
        mvaddch(y, x, '@');
    }

    while(isEnded) {
        clear();
        move(15,40);
        printw("Game Over");
        int i = wgetch(win);
    }
    endwin();
    return 0;
}
