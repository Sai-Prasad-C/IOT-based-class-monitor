/* * Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/


#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED1 6 //define green LED pin
#define LED2 5 //define red LED
#define trigpin1 7
#define trigpin2 2
#define echopin1 3
#define echopin2 4

int tvar = 1;
int s1var = 1;
char tuid[50] = "07 AC 37 21";
char tname[50] = "Mr. Arduino";
char tsub[50] = "Arduino";
char s1uid[50] = "57 13 8F C8";
char s1name[50] = "Student1";
void getid();
long time1, time2, dist1, dist2;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo; //define servo name

void setup()
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(3); //servo pin
  myServo.write(0); //servo start position
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop()
{
  pinMode(trigpin1, OUTPUT);
  digitalWrite(trigpin1, LOW);
  delayMicroseconds(5);

  digitalWrite(trigpin1, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigpin1, LOW);

  pinMode(echopin1, INPUT);
  time1 = pulseIn(echopin1, HIGH);

  dist1 = (time1 / 2) * 0.0343;
  /*
  Serial.print("Distance 1: ");
  Serial.println(dist1);
  */
  pinMode(trigpin2, OUTPUT);
  digitalWrite(trigpin2, LOW);
  delayMicroseconds(5);

  digitalWrite(trigpin2, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigpin2, LOW);

  pinMode(echopin2, INPUT);
  time2 = pulseIn(echopin2, HIGH);

  dist2 = (time2 / 2) * 0.0343;
  /*
  Serial.print("Distance 2: ");
  Serial.println(dist2);
  */
  if (tvar % 2 == 0)
  {
    if (dist1 < 65 && dist1 > 0)
    {
      analogWrite(LED1, 255);
    }
    else
    {
      analogWrite(LED1, 5);
    }
  }
  if (s1var % 2 == 0)
  {
    if (dist2 < 65 && dist2 > 0)
    {
      analogWrite(LED2, 255);
    }
    else
    {
      analogWrite(LED2, 5);
    }
  }
  // Look for new cards
    if ( mfrc522.PICC_IsNewCardPresent())
    {
      Serial.println("Detected");
      getid();
    }
}
void getid()
{
  while (1)
  {
    
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())
    {
      return;
    }
    //Show UID on serial monitor
    Serial.print("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    if (content.substring(1) == tuid && tvar % 2 != 0) //change here the UID of the card/cards that you want to give access
    {
      tvar += 1;
      Serial.println("Authorized access");
      Serial.print("Teacher Name: ");
      Serial.println(tname);
      Serial.print("Subject: ");
      Serial.println(tsub);
      Serial.println();
      analogWrite(LED1, 5);
      delay(500);
      break;
    }

    else if (content.substring(1) == s1uid && s1var % 2 != 0)
    {
      s1var += 1;
      Serial.println("Authorized access");
      Serial.print("Student Name: ");
      Serial.println(s1name);
      Serial.println();
      analogWrite(LED2, 5);
      delay(500);
      break;
    }
    else if (content.substring(1) == tuid  && tvar % 2 == 0)
    {
      tvar -= 1;
      Serial.println(" Exit code: Teacher");
      Serial.println();
      digitalWrite(LED1, LOW);
      delay(500);
      break;
    }

    else if (content.substring(1) == s1uid && s1var % 2 == 0)
    {
      s1var -= 1;
      Serial.println(" Exit Code: Student");
      Serial.println();
      digitalWrite(LED2, LOW);
      delay(500);
      break;
    }
  }
}
