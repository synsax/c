#include <stdlib.h>
#include <time.h>
#include <stdio.h>

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
            printf("%c",map[i][j]);
        }
        putchar('\n');
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
    int i;
    srand((unsigned)time(NULL));
    printf("RAND_MAX = %d\n",RAND_MAX);
    printf("rand = %d\n",rand());
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
    setup(st, stn, 0, 0);

    //draw();
    
    return 0;
}
