#include<stdio.h>

void main()
{
    FILE *pfile;
    FILE *image;
    int c;

    image=fopen("cc.bmp","wb");
    pfile=fopen("test.txt","r");

    while(fscanf(pfile,"%d",&c)!=EOF)
    {
        fputc(c,image);
    }

    fclose(pfile);
    fclose(image);
}
