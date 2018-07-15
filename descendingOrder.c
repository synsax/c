#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n = 0, *p;
	scanf("%d",&n);
	if(n<=0) return 0;
	p = (int *)calloc(n,sizeof(int));
	if(p == NULL) return EXIT_FAILURE;

	int i;
	for(i=0;i<n;i++) {
		scanf("%d",&p[i]);
	}

	int state = 1;
	while(state) {
		for(i=0;i<n-1;i++) {
			if(p[i] < p[i+1]) {
				int buff = p[i];
				p[i] = p[i+1];
				p[i+1] = buff;
			}
		}
		int c = 0;
		for(i=0;i<n-1;i++) {
			if(p[i] >= p[i+1]) {
				c++;
			}
		}
		if(c==n-1) break; 
	}
	for(i=0;i<n;i++) {
		printf("%d",p[i]);
		if(i!=n-1) putchar(' ');
	}
	putchar('\n');
	free(p);
	return 0;
}
