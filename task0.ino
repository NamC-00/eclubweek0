

// Pin definitions
const int POT1_PIN = A0;
const int POT2_PIN = A1;

const int BUZZER1_PIN = 3;
const int BUZZER2_PIN = 4;
const int BUZZER3_PIN = 5;

const int LED_PINS[] = {8, 9, 10, 11, 12};
const int NUM_LEDS = 5;

// Variables
int currentLed = 0;
unsigned long previousMillis = 0;

void setup() {
  // Initialize buzzer pins as outputs
  pinMode(BUZZER1_PIN, OUTPUT);
  pinMode(BUZZER2_PIN, OUTPUT);
  pinMode(BUZZER3_PIN, OUTPUT);
  
  // Initialize LED pins as outputs
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  
  // Turn off all buzzers initially
  digitalWrite(BUZZER1_PIN, LOW);
  digitalWrite(BUZZER2_PIN, LOW);
  digitalWrite(BUZZER3_PIN, LOW);
  
  // Turn off all LEDs initially
  allLedsOff();
}

void loop() {
  // Read potentiometer values
  int pot1Value = analogRead(POT1_PIN);
  int pot2Value = analogRead(POT2_PIN);
  
  // Control buzzers based on POT1 value
  controlBuzzers(pot1Value);
  
  // Control LED sequence based on POT2 value
  controlLeds(pot2Value);
}

void controlBuzzers(int potValue) {
  // Divide the 10-bit ADC range (0-1023) into 3 roughly equal parts
  int rangeSize = 1023 / 3;
  
  // Turn off all buzzers first
  digitalWrite(BUZZER1_PIN, LOW);
  digitalWrite(BUZZER2_PIN, LOW);
  digitalWrite(BUZZER3_PIN, LOW);
  
  // Activate the appropriate buzzer based on range
  if (potValue < rangeSize) {
    digitalWrite(BUZZER1_PIN, HIGH);
  } else if (potValue < rangeSize * 2) {
    digitalWrite(BUZZER2_PIN, HIGH);
  } else {
    digitalWrite(BUZZER3_PIN, HIGH);
  }
}

void controlLeds(int potValue) {
  // Map the potentiometer value to a delay between 100ms and 1000ms
  int ledDelay = map(potValue, 0, 1023, 100, 1000);
  
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= ledDelay) {
    previousMillis = currentMillis;
    
    // Turn off all LEDs
    allLedsOff();
    
    // Turn on the current LED
    digitalWrite(LED_PINS[currentLed], HIGH);
    
    // Move to the next LED
    currentLed = (currentLed + 1) % NUM_LEDS;
  }
}

void allLedsOff() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
}







