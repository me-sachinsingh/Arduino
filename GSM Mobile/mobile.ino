#include<Adafruit_GFX.h>
#include<UTFTGLUE.h>
#include<SoftwareSerial.h>
SoftwareSerial SIM(52,53);
SoftwareSerial BL(50,51);


UTFTGLUE LCD(0x9328,A2,A1,A3,A4,A0);

int r,g,b,x,y;

void setup() {
  Serial.begin(9600);
  SIM.begin(9600);
  BL.begin(38400);
  pinMode(A0,OUTPUT);
  digitalWrite(A0,1);
  LCD.InitLCD(LANDSCAPE);
  LCD.clrScr(); 
  Boot();
}

int command=-1;

void loop() {
  LCD.clrScr();
  LCD.setColor(random(0,255),random(0,255),random(0,255));
  LCD.drawRoundRect(0,0,319,79);
  keypadLayout();
  delay(2);
  keyDraw();
  delay(2);
  callFeatures();
  Serial.println("Entering Bluetooth");
  while(1) {
    if(BL.available()>0) {
       command=BL.read()-48; 
      }
      Serial.println(command);
      if(command!=-1) {
       BLControl();
       command = -1;
      } 
    }  

}

void Boot() {
  LCD.setTextSize(2);
  LCD.setColor(0,0,255);
  LCD.print("Booting",120,110);
   while(millis()<10000) {
    color();
    pos();
    LCD.drawPixel(x,y);
    delay(10);
   }
  LCD.clrScr();
  }

void pos() {
  x=random(0,320);
  y=random(0,240);
  }

void color() {
  r=random(0,255);
  g=random(0,255);
  b=random(0,255);
  LCD.setColor(r,g,b);
  }

void keypadLayout() {
  int row=80,incRow=40;
  int col=0,incCol=60;
  LCD.setColor(255,0,0);
  for(int i=0;i<4;i++) {
     LCD.drawLine(0,row,320,row);
     LCD.drawLine(col,80,col,240);
     row+=incRow;
     col+=incCol;
    }  
  LCD.drawLine(0,239,320,239);  
  LCD.drawLine(319,80,319,240);
}

void keyDraw() {
  long num=1;
  int X=24,Y=94;
  int keyDistX=60,keyDistY=40;
  LCD.setTextSize(2);
  LCD.setColor(255,255,255);
  for(int i=0;i<3;i++) {
     for(int j=0;j<3;j++) {
       LCD.setCursor(X,Y);
       LCD.printNumI(num,X,Y,0);
       num++;
       X+=keyDistX;
      }
      X=24;
      Y+=keyDistY;
    }
  LCD.print("X",X,Y);
  LCD.print("0",X+60,Y);
  LCD.print("#",X+120,Y);  
}

void callFeatures() {
  LCD.setColor(0,255,0);
  LCD.setTextSize(1);
  LCD.print("Delete",228,98);
  LCD.print("Call Logs",220,138);
  LCD.print("Contacts",223,178);
  LCD.print("Call",235,215);  
}

int shift = 30;
String number;
int valueX=320;

void BLControl() {
  valueX+=20;
  LCD.setTextSize(3);
  LCD.setCursor(20,31);
  LCD.setColor(255,0,0);
  switch(command) {
     case 0:
           number+="0";
           LCD.print(number,valueX,31);
           break;
     case 1:
           number+="1";
           LCD.print(number,valueX,31);
           break;
     case 2:
           number+="2";
           LCD.print(number,valueX,31);
           break;
     case 3:
           number+="3";
           LCD.print(number,valueX,31);
           break;
     case 4:
           number+="4";
           LCD.print(number,valueX,31);
           break;
     case 5:
           number+="5";
           LCD.print(number,valueX,31);
           break;
     case 6:
           number+="6";
           LCD.print(number,valueX,31);
           break;  
     case 7:
           number+="7";
           LCD.print(number,valueX,31);
           break;
     case 8:
           number+="8";
           LCD.print(number,valueX,31);
           break;
     case 9:
           number+="9";
           LCD.print(number,valueX,31);
           break;    
     case 52:
          number="";
          valueX=320; 
          command=-1;
          loop();          
          break;  
     case 55:
          MakeCall();
          number="";
          valueX=320;
          break; 
     case 56:
          HangCall();
          command=-1;
          loop();
          break;                                                     
    } 
    command=-1;
}

void MakeCall() {
  LCD.clrScr();
  LCD.setColor(255,0,0);
  LCD.setTextSize(3);
  LCD.print("Calling...",80,115);
  Serial.println(number);
  SIM.print("ATD");
  SIM.print(number);
  SIM.print(";\r\n");
}

void HangCall() {
  SIM.print("ATH\r\n");  
  LCD.clrScr();
  LCD.setColor(255,0,0);
  LCD.setTextSize(3);
  LCD.print("Call Ended",80,105);
  delay(1000);
}
