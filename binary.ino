const int ledPins[8] = { 13, 12, 11, 10, 9, 8, 7, 6 };

void setup() {
  Serial.begin(9600);
  // Initialize LEDs
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.println("Enter a number (0-255):");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();  

    if (input.length() == 0) {
      return;
    }

    if (input.equals("shutdown")) {
      for (int i = 0; i < 8; i++) {
        digitalWrite(ledPins[i], LOW);
      }
    }

    int num = input.toInt();

    // Validate input number
    if (num < 0 || num > 255) {
      Serial.println("Invalid number! 0-255");
    } else {
      Serial.print(num);
      Serial.println(" in binary: check Binary LED System :)");


      //Explanation Example:
      //       // 0000 1111
      //       // 15 >> 7 --> 0000000*0001111
      //--> 0000000*=0
      // The & 1 -- bit masking
      //-->00000001
      //-->00000000
      //so the bit value for bit 7 is actually 0 meaning off
      
      // Update the LEDs based on 15 in binary
      for (int i = 0; i < 8; i++) {
        int bitVal = (num >> (7 - i)) & 1;
        digitalWrite(ledPins[i], bitVal ? HIGH : LOW);
      }
    }

    Serial.println("Enter next number:");
  }
}