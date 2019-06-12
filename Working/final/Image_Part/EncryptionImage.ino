#include <SPI.h>
#include<SD.h>
#include<RH_ASK.h>

RH_ASK driver(4700, 7, 7);

int gcd(int n1, int phi);
int countprime(int n);

void setup() {
  Serial.begin(9600);
  SD.begin(4);
  driver.init();

//IMAGE TO BINARY**************************************************
  Serial.print("Image to Binary: ");
  SD.remove("binary.txt");
  File image = SD.open("aa.bmp", FILE_READ);
  File binary = SD.open("binary.txt", FILE_WRITE);
  int i, c;

  while ((c = image.read()) != EOF)
  {
    for (i = 0; i <= 7; i++)
    {
      if (c & (1 << (7 - i)))
      {
        binary.print('1');
      }
      else
      {
        binary.print('0');
      }
    }
  }
  image.close();
  binary.close();
  Serial.print("DONE\n");


  //**************************************************
  int p = 7;
  int q = 17;
  int n = p * q;
  int phi = (p - 1) * (q - 1);
  int size = countprime(n);
  int n1[size];

  int count = 0;
  for (int i = 2; i <= n; i++)
  {
    int isprime = 0;
    for (int j = 2; j <= i / 2; j++)
    {
      if (i % j == 0)
      {
        isprime = 1;
        break;
      }
    }
    if (isprime == 0 && n != 1 )
    {
      n1[count] = i;
      count++;
    }
  }

  Serial.print("\nn is: ");
  Serial.print(n);
  Serial.print("\nphi is: ");
  Serial.print(phi);

  i = 0;
  int cd = 0;
  int e;
  while (cd != 1)
  {
    i = i + 1;
    cd = gcd(n1[i], phi);
  }
  e = n1[i];
  Serial.print("\ne is: ");
  Serial.print(e);

  int val = 0;
  int d = 0;
  while (val != 1)
  {
    d = d + 1;
    val = (d * e) % phi;
  }
  Serial.print("\nd is: ");
  Serial.print(d);



  int dec;
  dec = e;
  int bin_len = 0;
  while (dec != 0)
  {
    dec /= 2;
    bin_len++;
  }
  int en[bin_len];
  dec = e;
  i = 0;
  while (dec > 0)
  {
    en[i] = dec % 2;
    i++;
    dec /= 2;
  }

  Serial.print("\nBinary of e is: ");
  for (i = bin_len - 1; i >= 0; i--)
  {
    Serial.print(en[i]);
  }
  Serial.print("\nNos. of digits of e is: ");
  Serial.print(bin_len);

  //ENCRYPTION**************************************************
  size = bin_len - 1;
  SD.remove("cipher.txt");
  binary = SD.open("binary.txt", FILE_READ);
  File cipher = SD.open("cipher.txt", FILE_WRITE);

  char ch;
  Serial.print("\n\nEncryption: ");
  while ((ch = binary.read()) != EOF)
  {
    int c = 1;
    for (p = size; p >= 0; p--)
    {
      if (en[p] == 1)
      {
        c = fmod(fmod(pow(c, 2), n) * ch, n);
      }
      else if (en[p] == 0)
      {
        c = fmod(pow(c, 2), n);
      }
    }
    cipher.print(c);
    cipher.print(" ");
  }
  binary.close();
  cipher.close();

  Serial.print("DONE\n");


  //TRANSMISSION**************************************************
  Serial.print("\nTransmitting: \n");
  cipher = SD.open("cipher.txt", FILE_READ);
  int final = 0;
  int msg;
  delay(10000);
  ch = cipher.read();
  while (ch != EOF)
  {
    if (ch != ' ')
    {
      msg = ch - '0';
      final = final * 10 + msg;
      ch = cipher.read();
    }
    else
    {
      String combine = String(final);
      combine = combine + " ";
      static char *text = combine.c_str();
      driver.send((uint8_t *)text, strlen(text));
      driver.waitPacketSent();
      Serial.print(text);
      delay(150);
      ch = cipher.read();
      final = 0;
    }
  }

  Serial.print("Done");
  Serial.print(millis());
}

void loop() {
}

int gcd(int a, int b)
{
  if (a == 0 || b == 0)
    return 0;
  if (a == b)
    return a;
  if (a > b)
    return gcd(a - b, b);
  return gcd(a, b - a);
}

int countprime(int n)
{
  int j;
  int isprime;
  int count = 0;
  for (int i = 2; i <= n; i++)
  {
    isprime = 0;
    for (int j = 2; j <= i / 2; j++)
    {
      if (i % j == 0)
      {
        isprime = 1;
        break;
      }
    }
    if (isprime == 0 && n != 1 )
    {
      count++;
    }
  }
  return count;
}

