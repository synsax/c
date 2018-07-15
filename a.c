#include <stdio.h>
    
struct {
    int x, y, z;
}typedef S;

void setup(S *s) {
    s->x = 10;
    s->y = 20;
    s->z = 30;
}

int main()
{
    S s;
    setup(&s);
    printf("x = %d\ny = %d\nz = %d\n",s.x,s.y,s.z);
    return 0;
}
