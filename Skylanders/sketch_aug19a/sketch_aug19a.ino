#include <SPI.h>
#include <MFRC522.h>
//#include <Adafruit_NeoPixel.h>

//defining pins that where used to connect the readers to the arduino. RST PIN is the same for all readers but the SSPIN should be special for each.
#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_1_PIN        10         // Configurable, take a unused pin, only HIGH/LOW required, must be different to SS 2
//#define SS_2_PIN        8         // Configurable, take a unused pin, only HIGH/LOW required, must be different to SS 1


/**
   Create an instance for each reader
*/
MFRC522 rfidReader0(SS_1_PIN, RST_PIN); // Instance of the class

String newStrUID0, oldStrUID0; //saves the id of the tag read from reader 0

/**
   Initialize.
*/
void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin();        // Init SPI bus

  // Init Reader 0
  rfidReader0.PCD_Init(SS_1_PIN, RST_PIN);
  Serial.print(F("Reader0 "));
  Serial.print(F(": "));
  rfidReader0.PCD_DumpVersionToSerial();

  Serial.print(" Setup complete!");
  pinMode(2, OUTPUT);
}

/**
   Main loop.
*/
void loop() {
digitalWrite (2, LOW);
  //if a new tag is on the reader then read it
  if (rfidReader0.PICC_IsNewCardPresent() && rfidReader0.PICC_ReadCardSerial()) {
    readOnReader0();
  }



}


/**
   If a new tag is present on this reader, read it and save its ID as string
*/
void readOnReader0() {
  newStrUID0 = String(rfidReader0.uid.uidByte[0]) + " " + String(rfidReader0.uid.uidByte[1]) + " " + String(rfidReader0.uid.uidByte[2]) + " " + String(rfidReader0.uid.uidByte[3]);
  //if (newStrUID0 != oldStrUID0) { //in case of new ID tag:
    Serial.println("this is the stringid");
    Serial.println(newStrUID0);
    oldStrUID0 = newStrUID0;
    if (newStrUID0 == "26 11 100 40") { //diamond
      digitalWrite(2, HIGH); //0 to 255
      delay(100);
    }
    if (newStrUID0 == "58 37 133 25") {// ninja
      digitalWrite(2, HIGH); //0 to 255
      delay(200);
    }
    if (newStrUID0 == "102 190 32 207") { //tree
      digitalWrite(2, HIGH); //0 to 255
      delay(300);
    }
    if (newStrUID0 == "20 202 177 153") { //blue tag1
      digitalWrite(2, HIGH); //0 to 255
      delay(400);
    }
     if (newStrUID0 == "212 223 22 220") { //blue tag2
      digitalWrite(2, HIGH); //0 to 255
      delay(500);
    }
  //}
  //    Serial.println(rfidReader0.uid.uidByte[0]); this works
  rfidReader0.PICC_HaltA();
  
  //stopReading(rfidReader0);
}


void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
