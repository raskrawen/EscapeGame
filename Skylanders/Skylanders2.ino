// Read rfid tags
#include <SPI.h>
#include <MFRC522.h>

//defining pins that where used to connect the readers to the arduino. RST PIN is the same for all readers but the SSPIN should be special for each.
#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_1_PIN        10         // Configurable, take a unused pin, only HIGH/LOW required, must be different to SS 2

/**
   Create an instance for each reader
*/
MFRC522 rfidReader0(SS_1_PIN, RST_PIN); // Instance of the class
String newStrUID0, oldStrUID0; //saves the id of the tag read from reader 0

String tags[5] = { "58 37 133 25", "102 190 32 207", "26 11 100 40", "20 202 177 153", "212 223 22 220" };
int numberOfTags = sizeof(tags);
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
  Serial.println(" Setup complete!");
  pinMode(2, OUTPUT);
}

/**
   Main loop.
*/
void loop() {
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
  for (int i=0;i<numberOfTags; i++) {
    if (newStrUID0 == tags[i]) {
      digitalWrite(2, HIGH); //0 to 255
      delay(100*i);
      digitalWrite (2, LOW);
      Serial.println(tags[i]);
  }
  }
  rfidReader0.PICC_HaltA();
}
