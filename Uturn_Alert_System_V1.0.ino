#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
LiquidCrystal_I2C Ulcd(0x26,16,2);
LiquidCrystal_I2C Dlcd(0x27,16,2);
Servo Ugate; 
Servo Dgate; 
int Uir1=11;
int Uir2=12;
int Dir1=10;
int Dir2=9;
int Uledr=2;
int Uledg=6;
int Dledr=7;
int Dledg=8;
int on=0;
int off=1;
int irvalues[4];
int Uir1v,Uir2v,Dir1v,Dir2v;
void setup() {
  pinMode(Uledr,OUTPUT);
  pinMode(Uledg,OUTPUT);
  pinMode(Dledr,OUTPUT);
  pinMode(Dledg,OUTPUT);

  pinMode(Uir1,INPUT);
  pinMode(Uir2,INPUT);
  pinMode(Dir1,INPUT);
  pinMode(Dir2,INPUT);
  
  Ugate.attach(5); 
  Dgate.attach(3); 
  Ugate.write(100);
  Dgate.write(0);
  
  Ulcd.init(); 
  Dlcd.init();
  Ulcd.backlight();
  Dlcd.backlight();
  Serial.begin(9600);
}

void loop() {
  int t2=0;
  if(t2==1)
  {
    Dir1=0;
    t2=0;
  }
  ReadIRs();
  int Flag=0;
  int t=0;
  if(Dir1v==1)
  {
    Dlcd.clear();
    Flag=1;
    while(Flag==1)
    {
      CloseUgate();
      OpenDgate();
    digitalWrite(Uledr,on);
    digitalWrite(Uledg,off);
    Ulcd.setCursor(0,0);
    Ulcd.print("Vehicle is");
    Ulcd.setCursor(0,1);
    Ulcd.print("Approaching");
    ReadIRs();
    Flag=2;
    while(Flag==2)
    {
      ReadIRs();
    if(Dir2v==1)
    {
      delay(250);
      CloseDgate();
      Flag=3;
    }
    }
    while(Flag==3)
    {
      ReadIRs();
    if(Uir2v==1)
    {
      OpenUgate();
      digitalWrite(Uledr,off);
      digitalWrite(Uledg,on);  
      Ulcd.clear();
      Flag=4;
      t=1;
    }
    }
    }
    while(t==1)
    {
        ReadIRs();
      if(Uir1v==1)
      {
        t=0;
        Uir1v==0;
        delay(500);
        CloseUgate();
        delay(250);
        break;
      }
    }
  }
  ReadIRs();
  int Flag2=0;
  if(Uir1v==1)
  {
    Ulcd.clear();
    Flag2=1;
    while(Flag2==1)
    {
      CloseDgate();
      OpenUgate();
    digitalWrite(Dledr,on);
    digitalWrite(Dledg,off);
    Dlcd.setCursor(0,0);
    Dlcd.print("Vehicle is");
    Dlcd.setCursor(0,1);
    Dlcd.print("Approaching");
    ReadIRs();
    Flag2=2;
    while(Flag2==2)
    {
      ReadIRs();
    if(Uir2v==1)
    {
      delay(500);
      CloseUgate();
      Flag2=3;
    }
    }
    while(Flag2==3)
    {
      ReadIRs();
    if(Dir2v==1)
    {
      OpenDgate();
      digitalWrite(Dledr,off);
      digitalWrite(Dledg,on);  
      Dlcd.clear();
      Flag2=4;
      t2=1;
    }
    }
  }
  while(t2==1)
    {
        ReadIRs();
      if(Dir1v==1)
      {
        t2=0;
        Dir1v==0;
        delay(500);
        CloseDgate();
        break;
      }
    }
  }
  Ulcd.clear();
  Ulcd.setCursor(0,0);
  Ulcd.print("HYD 150km ^");
  Dlcd.clear();
  Dlcd.setCursor(0,0);
  Dlcd.print("Goa 350km ^");
  }

void ReadIRs()
{
  Uir1v = not(digitalRead(Uir1));
  Uir2v = not(digitalRead(Uir2));
  Dir1v = not(digitalRead(Dir1));
  Dir2v = not(digitalRead(Dir2));
}

void OpenUgate()
{
  Ugate.write(0);
}
void CloseUgate()
{
  Ugate.write(100);
}
void OpenDgate()
{
  Dgate.write(100);
}
void CloseDgate()
{
  Dgate.write(0);

}

void UlcdAlert()
{
    Ulcd.setCursor(0,0);
    Ulcd.print("Vehicle is");
    Ulcd.setCursor(1,0);
    Ulcd.print("Approaching");
}
