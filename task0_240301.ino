const int POT1_PIN = A0;
const int POT2_PIN = A1;

const int BUZZER1_PIN = 3;
const int BUZZER2_PIN = 4;
const int BUZZER3_PIN = 5;

const int LED_PINS[] = {8, 9, 10, 11, 12};
const int NUM_LEDS = 5;

int currentLed = 0;
unsigned long previousMillis = 0;

void setup() {
  pinMode(BUZZER1_PIN, OUTPUT);
  pinMode(BUZZER2_PIN, OUTPUT);
  pinMode(BUZZER3_PIN, OUTPUT);
 
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }

  digitalWrite(BUZZER1_PIN, LOW);
  digitalWrite(BUZZER2_PIN, LOW);
  digitalWrite(BUZZER3_PIN, LOW);
  
  allLedsOff();
}

void loop() {
  int pot1Value = analogRead(POT1_PIN);
  int pot2Value = analogRead(POT2_PIN);
  
  controlBuzzers(pot1Value);
  
  controlLeds(pot2Value);
}

void controlBuzzers(int potValue) {
  int rangeSize = 1023 / 3;
  
  digitalWrite(BUZZER1_PIN, LOW);
  digitalWrite(BUZZER2_PIN, LOW);
  digitalWrite(BUZZER3_PIN, LOW);
  
  if (potValue < rangeSize) {
    digitalWrite(BUZZER1_PIN, HIGH);
  } else if (potValue < rangeSize * 2) {
    digitalWrite(BUZZER2_PIN, HIGH);
  } else {
    digitalWrite(BUZZER3_PIN, HIGH);
  }
}

void controlLeds(int potValue) {
  int ledDelay = map(potValue, 0, 1023, 100, 1000);
  
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= ledDelay) {
    previousMillis = currentMillis;
    
    allLedsOff();
    
    digitalWrite(LED_PINS[currentLed], HIGH);
    
    currentLed = (currentLed + 1) % NUM_LEDS;
  }
}

void allLedsOff() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
}

//https://www.tinkercad.com/things/egkosopqrd2-fantabulous-bombul?sharecode=0vKoneLWPrc3SHiSfDKIE2AspeYw-IOGq4IWMOo0Qdk





