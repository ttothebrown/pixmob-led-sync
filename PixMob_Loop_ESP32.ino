#include <Arduino.h>
#include <IRremote.h>

#define IR_SEND_PIN 13

String incomingString = "";
void setup() {
  IrSender.begin(IR_SEND_PIN);

  Serial.begin(115200);
  SerialBT.begin("PixMobSender");
}

void loop() {
  for(int i =0; i<8; i++) 
  {
    incomingString = Serial.readStringUntil('['); // read the incoming byte:
    incomingString = Serial.readStringUntil(']'); // read the incoming byte:
    String newVals;
    if(i == 0) newVals = "11132114121112211211111113121221111114241";
    if(i == 1) newVals = "22111214132111122424121221111114241";
    if(i == 2) newVals = "22111124121212122424121221111114241";
    if(i == 3) newVals = "1212112412121322132213241423241";
    if(i == 4) newVals = "11132114121112111111112213121221111114241";
    if(i == 5) newVals = "1111222413111212111324121221111114241";
    if(i == 6) newVals = "22111124131112122424121221111114241";
    if(i == 7) newVals = "1113211412111422131212121221111114241";
    int newLength = i==0 || i == 4 || i == 6 ? 41 : 35;
    if(i ==3) newLength = 31;
    if(i == 5 || i == 7) newLength = 37;
    uint16_t newRawData[newLength] = {};
    
    for (int j = 0; j < newVals.length(); j++ ) {
      int intVal = newVals.substring(j, j + 1).toInt() * 700;
      newRawData[j] = intVal;
    }
    IrSender.sendRaw(newRawData, newLength, 38);  // Send a raw data capture at 38kHz.
    delay(3);
  }
  delay(500);
}
