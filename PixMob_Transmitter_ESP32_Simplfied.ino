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
  if (Serial.available() > 0) {
    incomingString = Serial.readStringUntil('['); // read the incoming byte:
    incomingString = Serial.readStringUntil(']'); // read the incoming byte:
    int newLength = incomingString.toInt();
    uint16_t newRawData[newLength] = {};
    String newVals = Serial.readStringUntil(',');
    for (int i = 0; i < newVals.length(); i++ ) {
      int intVal = newVals.substring(i, i + 1).toInt() * 700;
      newRawData[i] = intVal;
    }
    IrSender.sendRaw(newRawData, newLength, 38);  // Send a raw data capture at 38kHz.
    delay(3);

  } else if (SerialBT.available() > 0) {
    incomingString = SerialBT.readStringUntil('['); // read the incoming byte:
    incomingString = SerialBT.readStringUntil(']'); // read the incoming byte:
    int newLength = incomingString.toInt();
    uint16_t newRawData[newLength] = {};

    String newVals = SerialBT.readStringUntil(',');
    for (int i = 0; i < newVals.length(); i++ ) {
      int intVal = newVals.substring(i, i + 1).toInt() * 700;
      newRawData[i] = intVal;
    }
    IrSender.sendRaw(newRawData, newLength, 38);  // Send a raw data capture at 38kHz.
    delay(4);
  }
}
