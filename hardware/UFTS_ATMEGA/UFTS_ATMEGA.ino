#define TMR_PIN 4
#define WATCHDOG_PIN 2

void setup() {
  randomSeed(analogRead(0));
  
  Serial.begin(115200);

  pinMode(TMR_PIN, OUTPUT);
  pinMode(WATCHDOG_PIN, INPUT);
}

void loop() {
  char buf[256];
  
  int watchdogValue = digitalRead(WATCHDOG_PIN);
  
  snprintf(buf, sizeof buf, "$%d; ", watchdogValue);

  Serial.print(buf);
  
  
  
  int randNumber = random(10);
  if (randNumber >= 3) {
    digitalWrite(TMR_PIN, HIGH);
  }

  delay(1);

  digitalWrite(TMR_PIN, LOW);

  delay(1);
}
