#include<Keypad.h>
#include<SPI.h>
#include<MFRC522.h>

#define RST_PIN 1   
#define SS_PIN 4   // Nếu dùng Arduino Mega 2560 thì đổi 10 thành 53
MFRC522 mfrc522(SS_PIN, RST_PIN); 

const byte cols = 4, rows = 4;
short holdDelay = 500;
char key;

String enterPass = "";
String myPass = "1314";

char keys[rows][cols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

byte rowPins[rows] = {5, 6, 7, 8};
byte colPins[cols] = {9, 10, 11, 12};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

#include<Wire.h>
#include<LiquidCrystal_I2C.h>

#include<WString.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello Master!");

  SPI.begin();        
  mfrc522.PCD_Init(); 
  Serial.println("Lectura del UID");

  Serial.begin(9600);
  Serial.print("Hello Master!");

  delay(2000);
}

void enterPassword(char c) {
  lcd.setCursor(0,0);
  lcd.print("Enter password:");
  lcd.setCursor(0,1);
  do {
    c = keypad.getKey();
    switch (c) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        lcd.print('*');
        enterPass += c;
        break;
      case '*':
        enterPass = "";
        lcd.setCursor(0,1);
        lcd.print("         ");
        lcd.setCursor(0,1);
        break;
      case '#':
        break;
      case 'A':
        if (enterPass.length() != 0) {
          enterPass.remove(enterPass.length() - 1);
          Serial.print(enterPass);
          Serial.print("\n");
        }
        lcd.setCursor(0,1);
        lcd.print("        ");
        lcd.setCursor(0,1);
        for (int i = 0; i < enterPass.length(); i++) {
          lcd.print('*');
        }
      default:
        break;
    }
  } while (c != '#');
}

void changePass(char c) {
  enterPassword(c);
  if (enterPass == enterPass) {
    lcd.clear();
    lcd.print("Enter new pass:  ");
    lcd.setCursor(0,1);
  }
  myPass = "";
  do {
    c = keypad.getKey();
    switch (c) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        lcd.print('*');
        myPass += c;
        break;
      case '*':
        myPass = "";
        lcd.setCursor(0,1);
        lcd.print("         ");
        lcd.setCursor(0,1);
        break;
      case '#':
        break;
      case 'A':
        if (myPass.length() != 0) {
          myPass.remove(myPass.length() - 1);
          Serial.print(myPass);
          Serial.print("\n");
        }
        lcd.setCursor(0,1);
        lcd.print("        ");
        lcd.setCursor(0,1);
        for (int i = 0; i < myPass.length(); i++) {
          lcd.print('*');
        }
      default:
        break;
    }
  } while (c != '#');
  lcd.clear();
  lcd.print("The password");
  lcd.setCursor(0,1);
  lcd.print("has been change!");
  enterPass = "";
}

void validPass() {
  lcd.setCursor(0,0);
  lcd.print("Welcome back!   ");
  lcd.setCursor(0,1);
  lcd.print("My Master!");
}

void invalidPass() {
  lcd.setCursor(0,0);
  lcd.print("Invalid pass!   ");
  lcd.setCursor(0,1);
  lcd.print("Trying enter   ");
}

void loop() {
  key = keypad.getKey();
  char c;
  switch(key) {
    case '*':
      lcd.clear();
      enterPassword(c);
      if (enterPass == myPass) {
        validPass();
      }
      else invalidPass();
      enterPass = "";
      break;
    case 'C':
      changePass(c);
      break;
    case 'B':
      lcd.clear();
      lcd.print("What're you find'in?");
    default:
      break;
  }

  if(mfrc522.PICC_IsNewCardPresent()) 
  {  
    if(mfrc522.PICC_ReadCardSerial()) 
    {
      Serial.print("Card UID:");
      for (byte i = 0; i < mfrc522.uid.size; i++) 
      {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);   
      } 
      Serial.println();
      mfrc522.PICC_HaltA();         
    }       
  } 

  if (key != NO_KEY) {
    Serial.print(key);
    Serial.print("\n");

    // lcd.setCursor(0,1);
    // lcd.print(key);
  }
}
