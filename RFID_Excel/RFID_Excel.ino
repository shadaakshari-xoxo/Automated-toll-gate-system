#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10 //RX slave select
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

byte card_ID[4]; //card UID size 4byte
byte Name1[4]={0x91,0x0D,0x84,0x30};//first UID card
byte Name2[4]={0x41,0xF3,0x67,0x09};//second UID card
byte Name3[4]={0x51,0x00,0xC3,0x09};//second UID card
byte Name4[4]={0x9C,0xAF,0x1E,0x4A};//second UID card
byte Name5[4]={0x83,0x89,0xCB,0x1A};//second UID card

//if you want the arduino to detect the cards only once
int NumbCard[5];//this array content the number of cards. in my case i have just two cards.
int j=0;        

int const RedLed=6;
int const GreenLed=5;
int const Buzzer=8;

String Name;//user name
long Number;//user number
int n ;//The number of card you want to detect (optional)  

void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  
  Serial.println("CLEARSHEET");                 // clears starting at row 1
  Serial.println("LABEL,Date,Time,Name,Number");// make four columns (Date,Time,[Name:"user name"]line 48 & 52,[Number:"user number"]line 49 & 53)

  pinMode(RedLed,OUTPUT);
  pinMode(GreenLed,OUTPUT);
  pinMode(Buzzer,OUTPUT);

   }
    
void loop() {
  //look for new card
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;//got to start of loop if there is no card present
 }
 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;//if read card serial(0) returns 1, the uid struct contians the ID of the read card.
 }
 
 for (byte i = 0; i < mfrc522.uid.size; i++) {
     card_ID[i]=mfrc522.uid.uidByte[i];

       if(card_ID[i]==Name1[i]){
       Name="shadaakshari";//user name
       Number=123456;//user number
       j=0;//first number in the NumbCard array : NumbCard[j]
      }
      else if(card_ID[i]==Name2[i]){
       Name="Thejasvini";//user name
       Number=789101;//user number
       j=1;//Second number in the NumbCard array : NumbCard[j]
      }
      else if(card_ID[i]==Name3[i]){
       Name="Kawsalya";//user name
       Number=789156;//user number
       j=2;//Second number in the NumbCard array : NumbCard[j]
      }
      else if(card_ID[i]==Name4[i]){
       Name="Kalagara";//user name
       Number=784501;//user number
       j=3;//Second number in the NumbCard array : NumbCard[j]
      }
      else if(card_ID[i]==Name5[i]){
       Name="Lalitha";//user name
       Number=734101;//user number
       j=4;//Second number in the NumbCard array : NumbCard[j]
      }
      else{
          digitalWrite(GreenLed,LOW);
          digitalWrite(RedLed,HIGH);
          goto cont;//go directly to line 85
     }
}
      //if(NumbCard[j] == 1){//to check if the card already detect
      //if you want to use LCD
      //Serial.println("Already Exist");
     // }
      //else
      {
      NumbCard[j] = 1;//put 1 in the NumbCard array : NumbCard[j]={1,1} to let the arduino know if the card was detecting 
      n++;//(optional)
      Serial.print("DATA,DATE,TIME," + Name);//send the Name to excel
      Serial.print(",");
      Serial.println(Number); //send the Number to excel
      digitalWrite(GreenLed,HIGH);
      digitalWrite(RedLed,LOW);
      digitalWrite(Buzzer,HIGH);
      delay(30);
      digitalWrite(Buzzer,LOW);
      Serial.println("SAVEWORKBOOKAS,Names/WorkNames");
      }
      delay(1000);
cont:
delay(2000);
digitalWrite(GreenLed,LOW);
digitalWrite(RedLed,LOW);

//if you want to close the Excel when all card had detected and save Excel file in Names Folder. in my case i have just 2 card (optional)
//if(n==2){
    
  //  Serial.println("FORCEEXCELQUIT");
 //   }
}
    
