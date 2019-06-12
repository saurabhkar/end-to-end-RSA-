#include<stdio.h>

char bytefromtext(char* text)
{
    int i;
    char result=0;
    for(i=0; i<8; i++)
    {
        if(text[i]=='1')
        {
            result |= (1<< (7-i) );
        }
    }
    return result;
}

void main()
{
    FILE *pfile;
    FILE *image;
    char buf[8];
    char c;
    int j=0;

    image=fopen("cc.bmp","wb");
    pfile=fopen("test.txt","r");

    while ((c = fgetc (pfile)) != EOF)
    {
        buf[j++]=c;
        if(j==8)
        {
            fputc(bytefromtext(buf),image);
            j=0;
        }
    }

    fclose(pfile);
    fclose(image);
}
