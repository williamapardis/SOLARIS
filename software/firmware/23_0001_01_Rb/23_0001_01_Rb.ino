//Libraries
#include <Arduino.h>          // required before wiring_private.h
#include "wiring_private.h"   // pinPeripheral() function
#include "RTClib.h"           // for ds3231 clock
#include <SPI.h>
#include <SD.h>

////////////SERCOM SETUP////////////////////////////////////////////////////////////////
//SERCOM PIN and PAD assigment for serial2 (PMT)
#define PIN_SERIAL2_RX 2   //D2
#define PAD_SERIAL2_RX (SERCOM_RX_PAD_3)
#define PIN_SERIAL2_TX 18  //A4
#define PAD_SERIAL2_TX (UART_TX_PAD_0)
Uart Serial2( &sercom0, PIN_SERIAL2_RX, PIN_SERIAL2_TX, PAD_SERIAL2_RX, PAD_SERIAL2_TX );

//SERCOM PIN and PAD assigment for serial3 (user interface)
#define PIN_SERIAL3_RX 13  //D13
#define PAD_SERIAL3_RX (SERCOM_RX_PAD_1)
#define PIN_SERIAL3_TX 12  //D12
#define PAD_SERIAL3_TX (UART_TX_PAD_0)
Uart Serial3( &sercom5, PIN_SERIAL3_RX, PIN_SERIAL3_TX, PAD_SERIAL3_RX, PAD_SERIAL3_TX); // 13(D13 =>PA22 => Sercom 5.1) , 12(D12 =>PA23 => Sercom 5.0)

Stream *SERIALOUT = &Serial2;

void SERCOM0_0_Handler() {
  Serial2.IrqHandler();
}
void SERCOM0_1_Handler() {
  Serial2.IrqHandler();
}
void SERCOM0_2_Handler() {
  Serial2.IrqHandler();
}
void SERCOM0_3_Handler() {
  Serial2.IrqHandler();
}

void SERCOM5_0_Handler() {
  Serial3.IrqHandler();
}
void SERCOM5_1_Handler() {
  Serial3.IrqHandler();
}
void SERCOM5_2_Handler() {
  Serial3.IrqHandler();
}
void SERCOM5_3_Handler() {
  Serial3.IrqHandler();
}

////////////PIN DEFINITIONS////////////////////////////////////////////////////////////////
const int chipSelect = A5;  //select pin for SD card
const int EN485 = 4;        //RS485 (pump coms) enable. high=TX, low=RX
const int rst   = 3;

const int BUFsize = 10;
//File name for datalog file
String logFN = "";
bool armed = true;

RTC_DS3231 rtc;

int Twait=0,Tstar=0,Tnow=0;
int CC=1;

void setup() {

  //enable RS485 as transmit
  pinMode(EN485, OUTPUT); digitalWrite(EN485, HIGH);
  pinMode(rst,OUTPUT);digitalWrite(rst,HIGH);

  //setting ADC resolution
  analogReadResolution(12);
  
  //begin USB, RS458/pump, RS232/PMT, and RS232/user interface at 9600 bruad
  Serial.begin(9600); Serial1.begin(9600); Serial2.begin(9600); Serial3.begin(9600);

  //SERCOM
  pinPeripheral(PIN_SERIAL2_RX, PIO_SERCOM_ALT);
  pinPeripheral(PIN_SERIAL2_TX, PIO_SERCOM_ALT);
  pinPeripheral(PIN_SERIAL3_RX, PIO_SERCOM_ALT);
  pinPeripheral(PIN_SERIAL3_TX, PIO_SERCOM_ALT);
  
  PRINT("initializing SD... ");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
  }
  PRINT("SD initialized\n");

  sendMotorCom("/_TR");

  int Tstart = 180000; //delay time in ms before start
  int timer = millis();
  
  while (millis() < Tstart) {

    delay(1000);

    if (millis() - timer > 5000) {
      timer = millis();
      if (armed) {
        PRINT("\nsystem is armed\n");
      }
      else {
        PRINT("\nsystem is not armed\n");
      }

      PRINT("starting in: ");
      PRINT(String((Tstart - millis()) / 1000));
      PRINT(" [sec]");

    }

    char Abuf[BUFsize];
    memset(Abuf, 0, sizeof Abuf);
    comCheck(Abuf,BUFsize);
    if (String(Abuf) == "disarm") {
      PRINT("\nSYSTEM DISARMED\n");
      armed = false;
      sendMotorCom("/4J0R");
      break;
    }
    else if(String(Abuf) == "upload"){

      Tstart=Tstart-millis();
      
      char fBuf[100];
      PRINT("\n");

      PRINT("current mission.txt will be deleted\n");
      PRINT("Sure you want to upload (Y/N): ");
      while(Serial.available()==0 && Serial3.available()==0){}
      comCheck(fBuf,100);
      PRINT(String(fBuf));PRINT("\n");

      if(String(fBuf)=="Y"){
        SD.remove("mission.txt");
      }
      else{
        digitalWrite(rst,LOW);
      }
      
      while(true){
      memset(fBuf, 0, sizeof fBuf);
        PRINT("input line: ");
        while(Serial.available()==0 && Serial3.available()==0){}
        comCheck(fBuf,100);     
        printLineToFile(String(fBuf),"mission.txt");
        PRINT(fBuf);PRINT("\n");
        if(String(fBuf)=="done"){
          break;
        }
      }
      Tstart=Tstart+millis();
    }
    else if(String(Abuf) == "reset"){
      Serial.println("RESETING");
      digitalWrite(rst,LOW);
    }
    else if(String(Abuf) == "skip"){
      break;
    }

    PRINT(".");

  }

  PRINT("initializing RTC... ");
  if (!rtc.begin()) {
    PRINT("Couldn't find RTC\n");
  }
  PRINT("RTC initialized\n");
//  if (rtc.lostPower()) {
//    PRINT("RTC lost power\n");
//    // following line sets the RTC to the date & time this sketch was compiled
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//    // This line sets the RTC with an explicit date & time, for example to set
//    // January 21, 2014 at 3am you would call:
//    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
//  }

  PRINT("setting filename... ");
  setFilename();
  PRINT("filename set to: "); PRINT(logFN); PRINT("\n");

  if (armed){
    PRINT("Printing file\n");
    printFile("mission.txt");
    DateTime now = rtc.now();
    Tstar=now.unixtime();
    Twait=sendMissionCommand(CC);
//    PRINT("next action in: ");PRINT(String(Twait));PRINT(" seconds\n");
//    PRINT("Starting from: ");PRINT(String(Tstar));PRINT(" unixtime\n");
    CC++;
  }


  //PMT initilization settings
  PRINT("setting up PMT...");
  Serial2.write("P1\r");  //integration time
  while (Serial2.available()) {
    Serial2.read();
  }
  Serial2.write("D\r");   //votage
  while (Serial2.available()) {
    Serial2.read();
  }
  Serial2.write("C\r");   //start continuous read
  PRINT("PMT initialized\n");
  delay(100);



}


bool MCF = false; //motor command flag
char buf[BUFsize], mybuf[4];
int PS1 = 0, PS2 = 0, PS3 = 0, PS4 = 0, PS5 = 0, PS6 = 0, PS7 = 0; //pump state: 1 on, 0 off
int PF1 = 2440, PF2 = 2440, PF3 = 2440, PF4 = 2440, PF5 = 2440, PF6 = 2440, PF7 = 2440; //pump flow: 0 to 160000

void loop() {

  if(armed){
  DateTime now = rtc.now();
  Tnow=now.unixtime();
    if(Tnow>=Tstar+Twait){
      Tstar=now.unixtime();
      Twait=sendMissionCommand(CC);
      CC++;
  //    PRINT("next action in: ");PRINT(String(Twait/1000));PRINT(" seconds\n");
  //    PRINT("Starting from: ");PRINT(String(Tstar));PRINT(" unixtime\n");
    }
  }
  
  memset(buf, 0, sizeof buf);   //empty char array buffer
  //delay(5);
  
  if (Serial3.available() > 0) {

    Serial3.readBytesUntil('|', buf, 10);
    Serial.print("BUFF: ");Serial.println(sizeof(buf));
    
    if (buf[0] == '/') {
      sendMotorCom(buf);
      Serial.print("Sending (1): ");
    }
    else if(String(buf) == "reset"){
      Serial.println("RESETING");
      digitalWrite(rst,LOW);
    }
//    else {
//      Serial.println(buf);
//      Serial2.print(buf);
//      Serial.print("Sending (2): ");
//    }
    Serial.println(buf);
  }

  dataAquire();


  
  while(Serial1.available()>0){
    Serial.print("MOTOR AVAILABLE: ");Serial.println(Serial1.available());
    Serial.write(Serial1.read());
  }

}

void dataAquire(){
  
  if (Serial2.available() > 0) {
    String data = "";
    data += isoTime();
    data += ',';
    delay(5);
    while (Serial2.available() > 0) {  // If anything comes in Serial1 (pins 0 & 1)
      Serial2.readBytes(mybuf, 4);
    }
    data += (uint32_t)mybuf[0] << 24 | (uint32_t)mybuf[1] << 16 | (uint32_t)mybuf[2] << 8 | (uint32_t)mybuf[3];
    //analog channels
    data += ',';data+=(float(analogRead(A0))/4095)*3.3;//Actual Temp
    //data += ',';data+=analogRead(A1);//Set Temp
    //data += ',';data+=analogRead(A2);//Limit
    //if pump on record velocity, if not state 0
    data += ','; if (PS1) {
      data += PF1;
    } else {
      data += '0';
    };
    data += ','; if (PS2) {
      data += PF2;
    } else {
      data += '0';
    };
    data += ','; if (PS3) {
      data += PF3;
    } else {
      data += '0';
    };
    data += ','; if (PS4) {
      data += PF4;
    } else {
      data += '0';
    };
    data += ','; if (PS5) {
      data += PF5;
    } else {
      data += '0';
    };
    data += ','; if (PS6) {
      data += PF6;
    } else {
      data += '0';
    };
    data += ','; if (PS7) {
      data += PF7;
    } else {
      data += '0';
    };
    Serial.print("Recieved (2): ");
    PRINT(data); PRINT("\n");
    printLineToFile(data,logFN);
  }
  
}

char * comCheck(char BUF[],int howBig) {

  memset(BUF, 0, sizeof BUF);   //empty char array buffer
  delay(5);

  if (Serial.available() > 0) {
    Serial.readBytesUntil('\r', BUF, howBig);
  }
  else if (Serial3.available() > 0) {
    Serial3.readBytesUntil('\r', BUF, howBig);
  }

  return BUF;

}



void PRINT(String text) {
  Serial.print(text);
  Serial3.print(text);
}



//returns iso formated time
String isoTime() {

  DateTime now = rtc.now();

  String t = "";

  t += String(now.year(), DEC);
  if (now.month() < 10) {
    t += '0';
  }
  t += String(now.month(), DEC);
  if (now.day() < 10) {
    t += '0';
  }
  t += String(now.day(), DEC);
  t += "T";
  if (now.hour() < 10) {
    t += '0';
  }
  t += String(now.hour(), DEC);
  if (now.minute() < 10) {
    t += '0';
  }
  t += String(now.minute(), DEC);
  if (now.second() < 10) {
    t += '0';
  }
  t += String(now.second(), DEC);

  return t;

}

void sendMotorCom(char buff[]){
  Serial1.println(buff);
  checkPumpChange(buff);
}

void checkPumpChange(char buff[10]) {

  if (buff[2] == 'P') {
    switch (buff[1]) {
      case '1':
        PS1 = 1;
        break;
      case '2':
        PS2 = 1;
        break;
      case '3':
        PS3 = 1;
        break;
      case '4':
        PS4 = 1;
        break;
      case '5':
        PS5 = 1;
        break;
      case '6':
        PS6 = 1;
        break;
      case '7':
        PS7 = 1;
        break;
    }
  }
  else if (buff[2] == 'T') {
    switch (buff[1]) {
      case '1':
        PS1 = 0;
        break;
      case '2':
        PS2 = 0;
        break;
      case '3':
        PS3 = 0;
        break;
      case '4':
        PS4 = 0;
        break;
      case '5':
        PS5 = 0;
        break;
      case '6':
        PS6 = 0;
        break;
      case '7':
        PS7 = 0;
        break;
    }
  }
  else if (buff[2] == 'V') {
    switch (buff[1]) {
      case '1':
        PF1 = atoi(&buff[3]);
        break;
      case '2':
        PF2 = atoi(&buff[3]);
        break;
      case '3':
        PF3 = atoi(&buff[3]);
        break;
      case '4':
        PF4 = atoi(&buff[3]);
        break;
      case '5':
        PF5 = atoi(&buff[3]);
        break;
      case '6':
        PF6 = atoi(&buff[3]);
        break;
      case '7':
        PF7 = atoi(&buff[3]);
        break;
    }
  }

}
