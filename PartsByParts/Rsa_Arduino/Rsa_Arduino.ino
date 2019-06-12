int p, q, n, phi, i, cd, e;

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
  for (i = 2; i <= n; i++)
  {
    isprime = 0;
    for (j = 2; j <= i / 2; j++)
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


void setup() {
  Serial.begin(9600);



  p = 101;
  q = 103;
  n = p * q;
  phi = (p - 1) * (q - 1);
  int size;
  size = countprime(n);
  int n1[size];


  int j;
  int isprime;
  int count = 0;
  for (i = 2; i <= n; i++)
  {
    isprime = 0;
    for (j = 2; j <= i / 2; j++)
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
  Serial.print("n is: ");
  Serial.print(n);
  Serial.print("\nphi is: ");
  Serial.print(phi);

  i = 0;
  cd = 0;
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


  char msg[] = "THE QUICK FOX JUMPED OVER THE DOG.";
  Serial.print("\nMsg is: ");
  Serial.print(msg);

  size = sizeof(msg) / sizeof(msg[0]);
  /*printf("\nAscii of msg is: ");
    for (i = 0; i < size - 1; i++)
    printf("%d ", msg[i]);*/

  //-------------------------------------------

  int bin = 0;
  int rem;
  i = 1;

  int dec;
  dec = e;
  while (dec != 0)
  {
    rem = dec % 2;
    dec /= 2;
    bin += rem * i;
    i *= 10;
  }
  Serial.print("\nBinary of e is: ");
  Serial.print(bin);

  int bin1;
  int bin_len = 0;
  bin1 = bin;
  while (bin1 != 0)
  {
    bin1 /= 10;
    bin_len ++;
  }
  Serial.print("\nNos. of digit of binary is: ");
  Serial.print(bin_len);

  int en[bin_len];
  count = bin_len;
  int digit;
  while (bin > 0)
  {
    digit = bin % 10;
    en[count - 1] = digit;
    bin = bin / 10;
    count--;
  }

  Serial.print("\nBinary of e in array is: ");
  for (i = 0; i < bin_len; i++)
  {
    Serial.print(en[i]);
  }




  //ENCRYPTION*****************************************************************

  size = bin_len;
  Serial.print("\nSize of e is: ");
  Serial.print(size);
  int z = 0;
  int str_e;
  int ct[strlen(msg)];
  int u;

  Serial.print("\nCipher Text is: ");

  for (z = 0; z < strlen(msg); z++)
  {
    int c = 1;
    for (p = 0; p < size; p++)
    {
      if (en[p] == 1)
      {
        c = fmod(fmod(pow(c, 2), n) * msg[z], n);
      }
      else if (en[p] == 0)
      {
        c = fmod(pow(c, 2), n);
      }
    }
    ct[z] = c;
    Serial.print(ct[z]);
    Serial.print(" ");
  }

  Serial.print("\n\n------------------------------------------------------------------------------------------------------------------------");

  int bin11[50];
  i = 0;

  dec = d;
  while (dec > 0)
  {
    bin11[i] = dec % 2;
    i++;
    dec /= 2;
  }


  bin_len = i;
  Serial.print("\nNos. of digit of binary is: ");
  Serial.print(bin_len);


  Serial.print("\nBinary of d in array is: ");
  for (i = bin_len - 1; i >= 0; i--)
  {
    Serial.print(bin11[i]);
    Serial.print(" ");
  }

  //DECRYPTION************************************
  size = bin_len - 1;
  z = 0;
  int pt[strlen(msg)];
  char pt1[strlen(msg)];

  for (z = 0; z < strlen(msg); z++)
  {
    int c = 1;
    for (p = size; p >= 0; p--)
    {
      if (bin11[p] == 1)
      {
        c = fmod(fmod(pow(c, 2), n) * ct[z], n);
      }
      else if (bin11[p] == 0)
      {
        c = fmod(pow(c, 2), n);
      }
    }
    pt[z] = c;
    pt1[z] = c;
  }
  Serial.print("\nPlain text is: ");
  for (z = 0; z < strlen(msg); z++)
  {
    Serial.print(pt[z]);
    Serial.print(" ");
  }
  Serial.print("\nPlain text is: ");
  for (z = 0; z < strlen(msg); z++)
  {
    Serial.print(pt1[z]);
    Serial.print(" ");
  }
}
void loop() {}
