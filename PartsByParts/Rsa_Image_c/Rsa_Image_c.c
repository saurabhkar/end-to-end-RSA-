#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int p,q,n,phi,i,cd,e;

int gcd(int n1,int phi);

int countprime(int n);
char bytefromtext(char* text);

int main()
{
    FILE *fptr;
    FILE *txt;
    int c;
    int i;

    fptr=fopen("aa.bmp","rb");
    txt=fopen("binary.txt","w");

    while ((c = fgetc (fptr)) != EOF)
    {
        for(i=0; i<=7; i++)
        {
            if(c&(1<<(7-i)))
            {
                fputc('1',txt);
            }
            else
            {
                fputc('0',txt);
            }
        }
    }
    fclose(fptr);
    fclose(txt);
    printf("***** Image to Binary Done *****\n\n");


    //*************************************************************************************************
    p = 7;
    q = 17;
    n = p*q;
    phi=(p-1)*(q-1);
    int size;
    size = countprime(n);
    int n1[size];


    int j;
    int isprime;
    int count = 0;
    for(i=2; i<=n; i++)
    {
        isprime = 0;
        for(j=2; j<=i/2; j++)
        {
            if(i%j==0)
            {
                isprime = 1;
                break;
            }
        }
        if(isprime ==0 && n!=1 )
        {
            n1[count] = i;
            count++;
        }
    }

    printf("n is: %d",n);
    printf("\nphi is: %d",phi);

    i = 0;
    cd = 0;
    while(cd!=1)
    {
        i = i+1;
        cd = gcd(n1[i],phi);
    }
    e = n1[i];

    printf("\ne is: %d",e);


    int val = 0;
    int d = 0;
    while(val!=1)
    {
        d = d+1;
        val = (d*e)%phi;
    }

    printf("\nd is: %d",d);

    //-------------------------------------------

    int bin=0;
    int rem;
    i=1;

    int dec;
    dec = e;
    while(dec!=0)
    {
        rem = dec%2;
        dec /=2;
        bin +=rem*i;
        i*=10;
    }
    printf("\nBinary of e is: %d",bin);

    int bin1;
    int bin_len = 0;
    bin1 = bin;
    while(bin1!=0)
    {
        bin1/=10;
        bin_len ++;
    }
    printf("\nNos. of digit of binary is: %d",bin_len);

    int en[bin_len];
    count =bin_len;
    int digit;
    while(bin>0)
    {
        digit = bin %10;
        en[count-1]= digit;
        bin = bin/10;
        count--;
    }

    printf("\nBinary of e in array is: ");
    for(i=0; i<bin_len; i++)
    {
        printf("%d ",en[i]);
    }

    //ENCRYPTION*****************************************************************

    size = bin_len;
    printf("\nSize of e is: %d",size);
    int z = 0;
    int str_e;
    int u;

    FILE *fp;
    fp = fopen("cipher.txt", "w");
    txt=fopen("binary.txt","r");
    char ch;

    while((ch = fgetc(txt)) != EOF)
    {
        int c = 1;
        for(p=0; p<size; p++)
        {
            if(en[p]==1)
            {
                c=fmod(fmod(pow(c,2),n)*ch,n);
            }
            else if(en[p]==0)
            {
                c=fmod(pow(c,2),n);
            }
        }
        fprintf(fp,"%d ",c);
    }
    fclose(fp);

    printf("\n\n------------------------------------------------------------------------------------------------------------------------");
    //**************************************************
    int bin11[50];
    i=0;

    dec = d;
    while(dec>0)
    {
        bin11[i] = dec%2;
        i++;
        dec /=2;
    }


    bin_len = i;;
    printf("\nNos. of digit of binary is: %d",bin_len);


    printf("\nBinary of d in array is: ");
    for(i=bin_len-1; i>=0; i--)
    {
        printf("%d ",bin11[i]);
    }

    //DECRYPTION************************************
    size = bin_len-1;
    z = 0;

    fp = fopen("cipher.txt", "r");
    FILE *pfile;
    pfile=fopen("test.txt","w");
    int num;
    while(fscanf(fp,"%d",&num)!=EOF)
    {
        int c = 1;
        for(p=size; p>=0; p--)
        {
            if(bin11[p]==1)
            {
                c=fmod(fmod(pow(c,2),n)*num,n);
            }
            else if(bin11[p]==0)
            {
                c=fmod(pow(c,2),n);
            }
        }
        fputc(c,pfile);
    }
    fclose(fp);
    fclose(pfile);

    //IMAGE RECREATION*******************************
    printf("\n\n***** IMAGE RECREATION DONE *****\n\n");
    FILE *image;
    char buf[8];
    char rec;
    j=0;

    image=fopen("cc.bmp","wb");
    pfile=fopen("test.txt","r");

    while ((rec = fgetc (pfile)) != EOF)
    {
        buf[j++]=rec;
        if(j==8)
        {
            fputc(bytefromtext(buf),image);
            j=0;
        }
    }

    fclose(pfile);
    fclose(image);
}


int gcd(int a,int b)
{
    if(a==0||b==0)
        return 0;
    if(a==b)
        return a;
    if(a>b)
        return gcd(a-b,b);
    return gcd(a,b-a);
}

int countprime(int n)
{
    int j;
    int isprime;
    int count = 0;
    for(i=2; i<=n; i++)
    {
        isprime = 0;
        for(j=2; j<=i/2; j++)
        {
            if(i%j==0)
            {
                isprime = 1;
                break;
            }
        }
        if(isprime ==0 && n!=1 )
        {
            count++;
        }
    }
    return count;
}

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
