/*
  SerialPassthrough sketch

  Some boards, like the Arduino 101, the MKR1000, Zero, or the Micro, have one
  hardware serial port attached to Digital pins 0-1, and a separate USB serial
  port attached to the IDE Serial Monitor. This means that the "serial
  passthrough" which is possible with the Arduino UNO (commonly used to interact
  with devices/shields that require configuration via serial AT commands) will
  not work by default.

  This sketch allows you to emulate the serial passthrough behaviour. Any text
  you type in the IDE Serial monitor will be written out to the serial port on
  Digital pins 0 and 1, and vice-versa.

  On the 101, MKR1000, Zero, and Micro, "Serial" refers to the USB Serial port
  attached to the Serial Monitor, and "Serial1" refers to the hardware serial
  port attached to pins 0 and 1. This sketch will emulate Serial passthrough
  using those two Serial ports on the boards mentioned above, but you can change
  these names to connect any two serial ports on a board that has multiple ports.

  created 23 May 2016
  by Erik Nyquist
*/

const int EN485 = 4; 

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(EN485, OUTPUT); digitalWrite(EN485, LOW);
  
}

char buf[15];
char buf1[10];

void loop() {
  
  if (Serial.available()) {      // If anything comes in Serial (USB),

    digitalWrite(EN485, HIGH);
    memset(buf, 0, sizeof buf);   //empty char array buffer
    
    Serial.readBytesUntil('|',buf, 10);
    Serial.print("recieved(0):");Serial.print(buf);Serial.print(" ---------> ");
    
    Serial1.write(buf);
    Serial1.write(13);
    Serial.print("sent(1):");Serial.println(buf);
    delay(6);
    digitalWrite(EN485, LOW);
    
    //sendMotorCom(buf);   
  }
  
  if (Serial1.available()) {     // If anything comes in Serial1 (pins 0 & 1)
    
    delay(5);
    
    memset(buf1, 0, sizeof buf1);   //empty char array buffer
    
    Serial.println(Serial1.available());
    
    Serial1.readBytes(buf1,7);
    Serial.print("recieved(1):");Serial.print(buf1);Serial.print(" ---------> ");
    
    Serial.print("sent(0):");Serial.println(buf1);

    Serial.println((uint32_t)buf1[3]);
    Serial.println((uint32_t)buf1[4]);


    

    
  }

  
}



void sendMotorCom(char buff[]){
  Serial1.println(buff);
  Serial.print("sent(1):");Serial.println(buff);
}
