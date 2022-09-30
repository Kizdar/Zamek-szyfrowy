#include <MFRC522.h>
#include <SPI.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9
#define czas_trwania 5000
const byte UID_karta[] = {0x60, 0x90, 0xF9, 0xA7};
const byte UID_brelok[] = {0xA3, 0xC2, 0x4C, 0x79};

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
boolean stan = false;
unsigned long czas;
int ile_razy_karta=0;

void setup() {
Serial.begin(9600);
SPI.begin();
rfid.PCD_Init (); 
lcd.begin(16,2);
lcd.setCursor(0, 0);
lcd.print ("Proba systemu");

}

void loop() {
 if(rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
 {
  if (rfid.uid.uidByte[0] == UID_karta[0] &&
      rfid.uid.uidByte[1] == UID_karta[1] &&
      rfid.uid.uidByte[2] == UID_karta[2] &&
      rfid.uid.uidByte[3] == UID_karta[3])
  {
    ile_razy_karta++;
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Otwarty");
  lcd.setCursor(0,1);
  lcd.print("Ilosc wejsc ");
  lcd.print(ile_razy_karta);
  stan = true;
  czas = millis() + czas_trwania;

  } else
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Nieoprawny");
    stan = false;
    }
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
  // zamkniecie po jakimś czasie
  if(stan && czas< millis())
  {
    lcd.clear();
  stan = false;
  lcd.setCursor(0,0);
  lcd.print("Zamkniete");
  }
  
}
