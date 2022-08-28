// Read rfid tags
#include <SPI.h>
#include <MFRC522.h>

//defining pins that where used to connect the readers to the arduino. RST PIN is the same for all readers but the SSPIN should be special for each.
#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_1_PIN        10         // Configurable, take a unused pin, only HIGH/LOW required, must be different to SS 2
/*
   SDA  10
   SCK  13
   MOSI 11
   MISO 12
   GND  GND
   RST 9
   3.3V 3.3V
*/
/**
   Create an instance for each reader
*/
MFRC522 rfidReader0(SS_1_PIN, RST_PIN); // Instance of the class
String newStrUID0, oldStrUID0; //saves the id of the tag read from reader 0

String tags[15] = { "48 242 24 170",
"31 242 75 30", "63 184 129 37", "202 119 199 37", "111 241 123 7", "100 217 208 53", "95 185 237 118",
"58 37 133 25", "102 190 32 207", "26 11 100 40", "20 202 177 153", 
"212 223 22 220" , "111 1 143 7", "17 225 130 99", "76 242 231 43" };
int numberOfTags = 15;
/**
   Initialize.
*/
void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  pinMode(LED_BUILTIN, OUTPUT);
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
  Serial.println(newStrUID0);
  for (int i = 0; i < numberOfTags; i++) {
    //Serial.println("in for loop: " + i);
    if (newStrUID0 == tags[i]) {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(500);                       // wait
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(2, HIGH); //0 to 255
      delay(50 * i + 50);
      digitalWrite (2, LOW);
      //Serial.println("no: " + i);
      Serial.println("known: " + tags[i]);
    }
  }
  rfidReader0.PICC_HaltA();
}
