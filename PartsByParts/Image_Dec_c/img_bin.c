#include<stdio.h>

void main()
{
    FILE *fptr;
    FILE *txt;
    int c;
    int count = 0;

    fptr=fopen("aa.bmp","rb");
    txt=fopen("test.txt","w");

    while ((c = fgetc (fptr)) != EOF)
    {
        fprintf(txt,"%d ",c);
        count++;
    }

    printf("%d",count);
    printf("\n%d",count*4);
    fclose(fptr);
    fclose(txt);
}
