#include <stdio.h>
#include <stdlib.h>

int pids[2];
FILE* fp;


int main()
{
	int i;
	char str[20];
	printf("\nEnter cmd ");
	scanf("%[^\n]s",str);
	
	fp=popen(str,"r");
	
	char c;
	while((c=getc(fp))!=EOF)
		putchar(c);
	
	printf("\n\n\n");
	pclose(fp);



}
