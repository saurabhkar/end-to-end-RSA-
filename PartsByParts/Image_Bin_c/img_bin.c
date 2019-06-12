#include<stdio.h>

void main()
{
    FILE *fptr;
    FILE *txt;
    int c;
    int i;
    int count = 0;

    fptr=fopen("aa.bmp","rb");
    txt=fopen("test.txt","w");

    printf("success");

    while ((c = fgetc (fptr)) != EOF)
    {
        for(i=0; i<=7; i++)
        {
            if(c&(1<<(7-i)))
            {
                fputc('1',txt);
                count++;
            }
            else
            {
                fputc('0',txt);
                count++;
            }
        }
    }
    printf(" %d",count);
    fclose(fptr);
    fclose(txt);
}
