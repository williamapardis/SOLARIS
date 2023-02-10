

void printLineToFile(String dataString,String FN){
  File dataFile = SD.open(FN, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
  }
  // if the file isn't open, pop up an error:
  else {
    PRINT("error opening ");PRINT(FN);PRINT("\n");
  }  
}


void setFilename(){

  DateTime now = rtc.now();

  logFN+=String(now.year(), DEC);
  if(now.month()<10){logFN+='0';}
  logFN+=String(now.month(), DEC);
  if(now.day()<10){logFN+='0';}
  logFN+=String(now.day(), DEC);
  SD.mkdir(logFN);
  delay(50);
  
  logFN+='/';
  if(now.hour()<10){logFN+='0';}
  logFN+=String(now.hour(), DEC);
  if(now.minute()<10){logFN+='0';}
  logFN+=String(now.minute(), DEC);
  if(now.second()<10){logFN+='0';}
  logFN+=String(now.second(), DEC);
  logFN+=".txt";

  File dataFile = SD.open(logFN, FILE_WRITE); // create + open the file on the SD card
  if (!dataFile) {Serial.println("couldnt create file");}
  dataFile.close();
    
}


void printFile(String FN){
  File tFile = SD.open(FN);

  // if the file is available, write to it:
  if (tFile) {
    PRINT("File available\n");
    while (tFile.available()) {
      Serial.write(tFile.read());
    }
    tFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.print(FN);
    Serial.println(" file doesn't exist.");
  }
}



String getLineN(String FN, int lineNumber){
  File myFile = SD.open(FN,FILE_READ);
  myFile.seek(0);
  char cr;
  
  for(unsigned int i = 0; i < (lineNumber -1);){
    cr = myFile.read();
    if(cr == '\n'){
      i++;
    }
  }
     
  char line[25];
  memset(line, 0, sizeof line);
  //Now we are at the right line
  myFile.readBytesUntil('\n', line, 25);
  myFile.close();
  //a for loop with a read limit might be a good idea

  return line;

}


int sendMissionCommand(int lineNumber){
  
  File myFile = SD.open("mission.txt",FILE_READ);
  char cr;

  //find approriate line
  myFile.seek(0);
  for(unsigned int i = 0; i < (lineNumber -1);){
    cr = myFile.read();
    if(cr == '\n'){
      i++;
    }
  }

  //count commas
  int j=0;
  for(unsigned int i=0;i<1;){
    cr = myFile.read();
    if(cr == '\n'){
      i++;
    }
    else if(cr == ','){
      j++;
    }
  }

  //find line again
  myFile.seek(0);  
  for(unsigned int i = 0; i < (lineNumber -1);){
    cr = myFile.read();
    if(cr == '\n'){
      i++;
    }
  }

  //send commmands
  char line[25];
  for(int i=0;i<j;i++){
    memset(line, 0, sizeof line);
    //Now we are at the right line
    myFile.readBytesUntil(',', line, 25);
    Serial.println(line);
    sendMotorCom(line);
    delay(25);
  }
  
  //get duration
  memset(line, 0, sizeof line);
  myFile.readBytesUntil('\n', line, 25);
  
  myFile.close();

  return atoi(line);
  
}
