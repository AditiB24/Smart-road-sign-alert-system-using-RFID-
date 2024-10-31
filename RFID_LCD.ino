#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN         9          // Reset pin for RFID
#define SS_PIN          10         // Slave Select pin for RFID

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD I2C address (0x27 is common for many displays)

/*Card UID:8C:FB:7D:B0
Card UID:CC:98:D6:B0
Card UID:CC:98:D6:B0
Card UID:5A:1:46:48
Card UID:2C:EE:72:B0
Card UID:8A:A5:43:22 */

byte accessUID1[4] = {0x8C, 0xFB, 0x7D, 0xB0}; // Replace this with your card's UID
byte accessUID2[4] = {0xCC, 0x98, 0xD6, 0xB0};
byte accessUID3[4] = {0x5A, 0x1, 0x46, 0x48};
byte accessUID4[4] = {0x2C, 0xEE, 0x72, 0xB0};
byte accessUID5[4] = {0x8A, 0xA5, 0x43, 0x22};
int greenPin = 2;
int redPin = 3;
int buzzerPin = 4;

void setup() {
  // Pin modes
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialize Serial Monitor
  Serial.begin(9600);
  while (!Serial);  // Wait for serial to initialize on some boards

  // Initialize SPI bus for RFID
  SPI.begin();
  mfrc522.PCD_Init();  // Initialize RFID reader
  mfrc522.PCD_DumpVersionToSerial();  // Output RFID reader details to Serial

  // Initialize the LCD
  lcd.init();
  lcd.backlight(); // Turn on the LCD backlight
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ready to Scan!");

  Serial.println(F("Scan a card to see the UID, SAK, and type..."));
}

void loop() {
  // Check if there's a new card present
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;  // If no card is present, return
  }

  // Select the card
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;  // If reading the card fails, return
  }

  // Compare the UID of the card with the stored UID
  if (mfrc522.uid.uidByte[0] == accessUID1[0] &&
      mfrc522.uid.uidByte[1] == accessUID1[1] &&
      mfrc522.uid.uidByte[2] == accessUID1[2] &&
      mfrc522.uid.uidByte[3] == accessUID1[3]) {
    
    // Access Granted
    Serial.println("Speed Limit 50");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Speed Limit 50");
    
    // Turn on Green LED
    digitalWrite(greenPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(2000);  // Keep the LED on for 2 seconds
    digitalWrite(greenPin, LOW);
  }else if (mfrc522.uid.uidByte[0] == accessUID2[0] &&
      mfrc522.uid.uidByte[1] == accessUID2[1] &&
      mfrc522.uid.uidByte[2] == accessUID2[2] &&
      mfrc522.uid.uidByte[3] == accessUID2[3]) {
    
    // Access Granted
    Serial.println("School Ahead");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("School Ahead");
    
    // Turn on Green LED
    digitalWrite(greenPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(2000);  // Keep the LED on for 2 seconds
    digitalWrite(greenPin, LOW);
  }else if (mfrc522.uid.uidByte[0] == accessUID3[0] &&
      mfrc522.uid.uidByte[1] == accessUID3[1] &&
      mfrc522.uid.uidByte[2] == accessUID3[2] &&
      mfrc522.uid.uidByte[3] == accessUID3[3]) {
    
    // Access Granted
    Serial.println("Merge");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Merge");
    
    // Turn on Green LED
    digitalWrite(greenPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(2000);  // Keep the LED on for 2 seconds
    digitalWrite(greenPin, LOW);
  }else if (mfrc522.uid.uidByte[0] == accessUID4[0] &&
      mfrc522.uid.uidByte[1] == accessUID4[1] &&
      mfrc522.uid.uidByte[2] == accessUID4[2] &&
      mfrc522.uid.uidByte[3] == accessUID4[3]) {
    
    // Access Granted
    Serial.println("Slippery Road");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Slippery Road");
    
    // Turn on Green LED
    digitalWrite(greenPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(2000);  // Keep the LED on for 2 seconds
    digitalWrite(greenPin, LOW);
  }else if (mfrc522.uid.uidByte[0] == accessUID5[0] &&
      mfrc522.uid.uidByte[1] == accessUID5[1] &&
      mfrc522.uid.uidByte[2] == accessUID5[2] &&
      mfrc522.uid.uidByte[3] == accessUID5[3]) {
    
    // Access Granted
    Serial.println("No horn");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Horn");
    
    // Turn on Green LED
    digitalWrite(greenPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(2000);  // Keep the LED on for 2 seconds
    digitalWrite(greenPin, LOW);
  }
  
  else {
    // Access Denied
    Serial.println("Access Denied");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    
    // Turn on Red LED and Buzzer
    digitalWrite(redPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(1000);  // Keep them on for 1 second
    digitalWrite(redPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }

  // Halt PICC to stop reading the card
  mfrc522.PICC_HaltA();
}
