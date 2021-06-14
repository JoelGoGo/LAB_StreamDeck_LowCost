//#include <HID-Project.h>
//proyecto para ARDUINO UNO
//hacer update del frimware con HoodLoader2
//sino usar Arduino Leonardo, Arduino Micro, and Pro Micro

uint8_t buf[8] = { 0 };   //Keyboard report buffer
#define PIN_CAM 4 // Pin for OPEN THE CAM
#define PIN_REC 5 // Pin for RECORD THE SCREEN
#define PIN_SHARE 6 // Pin for SHARE SCREEN
#define PIN_MUTE 7 // Pin for MUTE 
#define POT_VOLUMEN A0// Pin for UP OR DOWN VOLUMEN, HAY QUE HACER POTENCIOMETRO
int ledA = 11;
int ledB = 10;
int ledC = 9;
int ledD = 8;

int boto1= LOW;
int boto2= LOW;
int boto3= LOW;
int boto4= LOW;

int contB1 = 0;
int contB2 = 0;
int contB3 = 0;
int contB4 = 0;
void setup() {
  Serial.begin(9600); //Setup Serial communication
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
  pinMode(ledD, OUTPUT);
  pinMode(PIN_CAM, INPUT); //alt + V
  pinMode(PIN_REC, INPUT); //alt + R
  pinMode(PIN_SHARE, INPUT); //alt + S
  pinMode(PIN_MUTE, INPUT); //alt + A
}

void loop() {
  int pot = analogRead (A0);
//definir 
  boto1 = digitalRead (PIN_CAM);
  boto2 = digitalRead (PIN_REC);
  boto3 = digitalRead (PIN_SHARE);
  boto4 = digitalRead (PIN_MUTE);
  if (boto1 == LOW) { 
    buf[2] = 26;  //hablo con jow
    digitalWrite (ledA, HIGH);
    contB1++;
    if (contB1%2 != 0){
    digitalWrite (ledA, LOW);
    }
    BootKeyboard.press(KEY_LEFT_ALT);
    BootKeyboard.write("V");
    BootKeyboard.release(KEY_LEFT_ALT);
    Serial.println("OPEN CAM");
    delay(1000);
    releaseKey();
  }
  else if (boto2 == LOW) { 
    buf[2] = 26;   
    digitalWrite(ledD, HIGH);
    contB2++;
    if (contB2%2 != 0){
    digitalWrite (ledD, LOW);
    }
    BootKeyboard.press(KEY_LEFT_ALT);
    BootKeyboard.write("R");
    BootKeyboard.release(KEY_LEFT_ALT);
    Serial.println("RECORD SCREEN");
    delay(1000);
    releaseKey();
  }
  else if (boto3 == LOW) { 
    buf[2] = 26;   //
    digitalWrite (ledB, HIGH);
    contB3++;
    if (contB3%2 != 0){
    digitalWrite (ledB, LOW);
    }
    BootKeyboard.press(KEY_LEFT_ALT);
    BootKeyboard.write("S");
    BootKeyboard.release(KEY_LEFT_ALT);
    Serial.println("SHARE SCREEN");
    delay(1000);
    releaseKey();
  }
  else if (boto4 == LOW) { 
    buf[2] = 26;   //
    digitalWrite (ledC, HIGH);
    contB4++;
    if (contB4%2 != 0){
    digitalWrite (ledC, LOW);
    }
    BootKeyboard.press(KEY_LEFT_ALT);
    BootKeyboard.write("A");
    BootKeyboard.release(KEY_LEFT_ALT);
    Serial.println("MUTE");
    delay(1000);
    releaseKey();
  }
  else if (pot > 0){
    Serial.println ((pot)/10 -2 );
    while (Serial.println ((pot)/10 -2) < 0){
      pot++;
      n++; if (n > 100) n = 100;
      Consumer.write(MEDIA_VOL_UP);
    }
    else {
      n--; if (n < 0) n = 0;
      Consumer.write(MEDIA_VOL_DOWN);
    }
    }
    delay(1);
  }
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);  
}
