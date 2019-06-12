      #include<SD.h>
      #include<SPI.h>
      File fptr;
      File txt;
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
      
        
        // open a new file and immediately close it:
        Serial.println("Creating example.txt...");
        txt = SD.open("test.txt", FILE_READ);
        fptr = SD.open("cc.bmp", FILE_WRITE);
      
        char buf[8];
        int c;
        int j = 0;
        while ((c = txt.read()) != EOF)
        {
          buf[j++] = c;
          if (j == 8)
          {
            fptr.print(bytefromtext(buf));
            j = 0;
          }
        }
        Serial.print("done");
      
        txt.close();
        fptr.close();
      
      
      }
      
      void loop() {
        // put your main code here, to run repeatedly:
      
      }
