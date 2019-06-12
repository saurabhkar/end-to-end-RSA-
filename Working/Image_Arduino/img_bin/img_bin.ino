
#include<SD.h>
#include<SPI.h>
File fptr;
File txt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  SD.remove("test.txt");
  // open a new file and immediately close it:
  Serial.println("Converting image !! Please Wait !!!!!!");
  fptr = SD.open("aa.bmp", FILE_READ);
  txt = SD.open("test.txt", FILE_WRITE);

  int c;
  int i;
  int count = 0;
  while ((c = fptr.read()) != EOF)
  {
    for (i = 0; i <= 7; i++)
    {
      if (c & (1 << (7 - i)))
      {
        txt.print('1');
        count++;
      }
      else
      {
        txt.print('0');                                                                                   
        count++;
      }
    }
  }
  Serial.println(count);
  Serial.println(count * 4);
  fptr.close();
  txt.close();
  Serial.print("Done");
}


void loop() {

}
