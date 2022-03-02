/*
 * CONTINUITY TESTER
 * -----------------
 * This is a little code snippet that runs on Arduino to test
 * continuity between it's own pins. Perfect to find matrix pinouts
 * or other schematics.
 * 
 * It's important that the pin has  internal pull-up resistors, otherwise
 * you'd short the pins out and you could burn the controller.
 * 
 * Author: Martín Durán
 */


// THIS IS MEANT FOR ARDUINO UNO/NANO, ADAPT IT TO ANY BOARD
// ALSO YOU CAN USE ANALOG PINS (14 TO 18)

#define START_PIN 2
#define END_PIN 12

#define TIME_BETWEEN_READINGS 50

int main() {
  init();
  Serial.begin(115200);
  
  // Initialize
  for(int pin = START_PIN; pin <= END_PIN; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }

  // Evaluate
  while(true) {
    Serial.println("\nTesting...\n----------");
    for(int readingPin = START_PIN; readingPin <= END_PIN; readingPin++) {
      pinMode(readingPin, INPUT_PULLUP);
      for(int testingPin = START_PIN; testingPin <= END_PIN; testingPin++) {
        if(testingPin == readingPin)
          continue;
  
        digitalWrite(testingPin, LOW);
        if(!digitalRead(readingPin) && readingPin < testingPin) // Last comparsion to avoid duplicates in the same cycle
          Serial.println(String(readingPin) + " <==> " + String(testingPin));
        digitalWrite(testingPin, HIGH);
      }
      pinMode(readingPin, OUTPUT);
      pinMode(readingPin, HIGH);
    }

    delay(TIME_BETWEEN_READINGS);
  }
}
