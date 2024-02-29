#include "SDLogger.hh"

SDLogger::SDLogger(){
  if(Serial) Serial.println("Initializing SD card...");
  if (!SD.begin()) {
    if(Serial) Serial.println("initialization failed!");
    while (1) {
      digitalWrite(RED, HIGH);
      delay(1000);
      digitalWrite(RED, LOW);
      delay(1000);
    }
  } else {
    if(Serial) Serial.println("SD Initialized");
  }
  openFile();
}


SDLogger::SDLogger(String newFileName){
  if(Serial) Serial.println("Initializing SD card...");
  if (!SD.begin()) {
    if(Serial) Serial.println("initialization failed!");
    while (1) {
      digitalWrite(RED, HIGH);
      delay(1000);
      digitalWrite(RED, LOW);
      delay(1000);
    }
  } else {
    if(Serial) Serial.println("SD Initialized");
  }
  openFile(newFileName);
}

void SDLogger::openFile(){
  //less stupid naming convention - 0000.csv to 9999.csv
  //look through SD card, find the next available filename
  bool fileavail = false;
  int i = 0;
  while (!fileavail) {  
    if (i < 10)
      fileName = String("000" + String(i) + ".csv");
    else if (i < 100)
      fileName = String("00" + String(i) + ".csv");
    else if (i < 1000)
      fileName = String("0" + String(i) + ".csv");
    else
      fileName = String(String(i) + ".csv");
    fileavail = !SD.exists(fileName);
    i++;
  }
  flightData = SD.open(fileName, FILE_WRITE);
  if(Serial) Serial.println("Writing to File: " + fileName);
  // Write the headers:
  if (flightData) {
    if(Serial) Serial.print("Writing to " + fileName);
    flightData.print("Time[us], Temp[C], Pressure[hPa],");
    flightData.print(" Omega_1[rad/s], Omega_2[rad/s], Omega_3[rad/s], acc_1[g], acc_2[g], acc_3[g],");
    flightData.println(" mag_1[uT], mag_2[uT], mag_3[uT]");
    flightData.close();
    if(Serial) Serial.println("...headers done.");
    fileName = flightData.name();
  } else {
    if(Serial) Serial.println("error opening " + fileName);
    //red light means stop
    while (1) {
      digitalWrite(RED, HIGH);
      delay(500);
      digitalWrite(RED, LOW);
      delay(500);
    }
  }
}

void SDLogger::openFile(String newFileName){
  fileName = newFileName;
  flightData = SD.open(fileName, FILE_WRITE);
  if(Serial) Serial.println("Writing to File: " + fileName);
  // Write the headers:
  if (flightData) {
    if(Serial) Serial.print("Writing to " + fileName);
    flightData.print("Time[us], Temp[C], Pressure[hPa],");
    flightData.print(" Omega_1[rad/s], Omega_2[rad/s], Omega_3[rad/s], acc_1[g], acc_2[g], acc_3[g],");
    flightData.println(" mag_1[uT], mag_2[uT], mag_3[uT]");
    flightData.close();
    if(Serial) Serial.println("...headers done.");
    fileName = flightData.name();
  } else {
    if(Serial) Serial.println("error opening " + fileName);
    //red light means stop
    while (1) {
      digitalWrite(RED, HIGH);
      delay(500);
      digitalWrite(RED, LOW);
      delay(500);
    }
  }
}

void SDLogger::writeLog(float acc1, float acc2, float acc3, float gy1, float gy2, float gy3, float mag1, float mag2, float mag3, float temp, float pressure, float t_now){
    flightData.print(String(t_now) + ',' + String(temp) + ',' + String(pressure) + ',');
    flightData.print(String(gy1) + ',' + String(gy2) + ',' + String(gy3) + ',');
    flightData.print(String(acc1) + ',' + String(acc2) + ',' + String(acc3) + ',');
    flightData.println(String(mag1) + ',' + String(mag2) + ',' + String(mag3));
    flightData.flush();

}

void SDLogger::closeFile(){
    if (flightData.peek()!=0){
        flightData.close();
    }
}

void SDLogger::writeLog(){}