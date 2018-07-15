#include <stdio.h>

int main()
{
    char *st[] = {
        "######################",
        "#                    #",
        "#          #         #",
        "#          #         #",
        "#    $     #         #",
        "#          #         #",
        "#          #         #",
        "#####################8",
    };
    printf("%c\n",st[7][21]);
    printf("%d\n",sizeof(st)/sizeof(st[0][0]));
    return 0;
}
