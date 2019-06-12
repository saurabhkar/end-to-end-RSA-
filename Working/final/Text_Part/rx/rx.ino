#include <RH_ASK.h>
// Include dependant SPI Library
#include <SPI.h>

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

void setup()
{
  // Initialize ASK Object
  rf_driver.init();
  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop()
{
  // Set buffer to size of expected message
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN] = {0};
  char *temp;
  int ct[50];
  String msg_len;
  uint8_t buflen = sizeof(buf);
  int count = 0;
  // Check if received packet is correct size
  if (rf_driver.recv(buf, &buflen))
  {

    // Message received with valid checksum
    Serial.print("Cipher Text: ");
    temp = (char*)buf;
    char *pt;
    pt = strtok( temp, ",");

    int i = 0;

    while (pt != NULL)
    {
      int a = atoi(pt);
      ct[i] = a;
      count++;
      pt = strtok (NULL, ",");
      i++;
    }

  }

  for (int i = 1; i < count; i++)
  {
    Serial.print(ct[i]);
    Serial.print(" ");
  }
  int n = ct[0];
  int bin11[50];
  int i = 0;
  int d = 463;
  int dec = d;
  while (dec > 0)
  {
    bin11[i] = dec % 2;
    i++;
    dec /= 2;
  }


  int bin_len = i;;
  //Serial.println(bin_len);



  //Serial.println("Binary of d in array is :");
  for (int i = bin_len - 1; i >= 0; i--)
  {
    // printf("%d ",bin11[i]);
    // Serial.print("\t");
    // Serial.print(bin11[i]);
  }

  //DECRYPTION*******


  int size = bin_len - 1;
  int z = 0;
  int pt[count];
  char pt1[count];

  //printf("\nAscii of Plain Text is: ");
  // Serial.println("Ascii of Plain text is :");
  for (z = 1; z < count; z++)
  {
    int c = 1;
    for (int p = size; p >= 0; p--)
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
    //printf("%d ",pt[z]);
    // Serial.print("\t");
    // Serial.print(pt[z]);
  }
  // printf("\nPlain text is: ");
  // Serial.println("\nPlain text is: ");

  //Serial.print("\n");
  for (z = 1; z < count; z++)
  {
    //printf("%c",pt[z]);

    Serial.print(pt1[z]);
  }
  // Serial.print(" ");
  delay(1000);
}



























