#include <SPI.h>
#include<SD.h>

char bytefromtext(char* text);

File cipher;

void setup(){
 
  Serial.begin(9600);

  SD.begin(4);
  //************************************************************************************
  SD.remove("cipher.txt");
}

  void setup()
  {
 Serial.begin(9600); 
 SD.begin(4);
 //************************************************************************************
 Serial.println("Start");
 
 int n=119;
 int d=77;
 int dec = d;
 int bin_len = 0;
 while (dec != 0)
 {
 dec /= 2;
 bin_len++;
 }
 
 int bin11[bin_len];
 dec = d;
 int i = 0;
 while (dec > 0)
 {
 bin11[i] = dec % 2;
 i++;
 dec /= 2;
 }
 
 Serial.print("\nBinary of d is: ");
 for (i = bin_len - 1; i >= 0; i--)
 {
 Serial.print(bin11[i]);
 }
 Serial.print("\nNos. of digits of d is: ");
 Serial.print(bin_len);
 
 
 //DECRYPTION**************************************************
 int size = bin_len - 1;
 File cipher = SD.open("cipher.txt", FILE_READ);
 File test;
 SD.remove("test.txt");
 test = SD.open("test.txt", FILE_WRITE);
 char num;
 Serial.print("\n\nDecryption: ");
 
 int msg;
 int final = 0;
 num = cipher.read();
 while (num != EOF)
 {
 if (num != ' ')
 {
 msg = num - '0';
 final = final * 10 + msg;
 num = cipher.read();
 }
 else
 {
 int c = 1;
 for (int p = size; p >= 0; p--)
 {
 if (bin11[p] == 1)
 {
 c = fmod(fmod(pow(c, 2), n) * final, n);
 }
 else if (bin11[p] == 0)
 {
 c = fmod(pow(c, 2), n);
 }
 }
 test.print((char)c);
 num = cipher.read();
 final = 0;
 }
 
 }
 test.close();
 cipher.close();
 Serial.print("DONE\n");
 
 // IMAGE   RECREATION**************************************************
 Serial.print("\nImage Recreation: ");
 SD.remove("new.bmp");
 test = SD.open("test.txt", FILE_READ);
 File image = SD.open("new.bmp", FILE_WRITE);
 char rec;
 char buf[8];
 int j = 0;
 while ((rec = test.read()) != EOF)
 {
 buf[j++] = rec;
 if (j == 8)
 {
 image.print(bytefromtext(buf));
 j = 0;
 }
 }
 Serial.print("Done");
 
 test.close();
 image.close();
 }
 
void loop() { }

 char bytefromtext(char* text)
 {
 int i;
 char result = 0;
 for (i = 0; i < 8; i++)
 {
 if (text[i] == '1')
 {
 result |= (1 << (7 - i) );
 }
 }
 return result;
 }

