const int MIN_SPEED = 50;
const int MAX_SPEED = 1000;
const int SPEED_STEP = 50;

int speed = 300;

const byte ledPins[] = {4, 5, 6, 7};
const byte ledCount = 4;

// Arduino D4-D7 correspond to PORTD bits 4-7.
const byte ledMask = 0b11110000;

void setup() {
  // Configure D4-D7 as outputs using DDRD.
  DDRD |= ledMask;

  // Initially turn all LEDs OFF.
  PORTD &= ~ledMask;

  Serial.begin(9600);
  Serial.println("4-LED Scanner Ready");
  Serial.print("New Speed: ");
  Serial.print(speed);
  Serial.println(" ms");
}

void loop() {
  checkSerial();

  // Scan forward: D4 -> D5 -> D6 -> D7
  for (byte i = 0; i < ledCount; i++) {
    scanLED(ledPins[i]);
  }

  // Scan backward: D6 -> D5
  for (int i = ledCount - 2; i > 0; i--) {
    scanLED(ledPins[i]);
  }
}

void scanLED(byte pin) {
  checkSerial();

  // Turn OFF all scanner LEDs.
  PORTD &= ~ledMask;

  // Turn ON the selected LED using PORTD.
  PORTD |= (1 << pin);

  delay(speed);
}

void checkSerial() {
  while (Serial.available() > 0) {
    char command = Serial.read();

    if (command == 'f' || command == 'F') {
      speed -= SPEED_STEP;

      if (speed < MIN_SPEED) {
        speed = MIN_SPEED;
      }

      printSpeed();
    }
    else if (command == 's' || command == 'S') {
      speed += SPEED_STEP;

      if (speed > MAX_SPEED) {
        speed = MAX_SPEED;
      }

      printSpeed();
    }
  }
}

void printSpeed() {
  Serial.print("New Speed: ");
  Serial.print(speed);
  Serial.println(" ms");
}
