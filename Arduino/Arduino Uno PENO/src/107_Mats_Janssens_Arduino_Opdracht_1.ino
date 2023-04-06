// Eerste Opdracht

void setup() {
  init_led_loop();
}

void loop() {
  blink_led_loop();
}


// For loop led leds als output
void init_led_loop () {
  for (int i = 2; i<=8; i=i+1) {
    pinMode(i, OUTPUT);
  }
}

// For loop led 1s branden
void blink_led_loop() {
  for (int i = 2; i<=8; i=i+1) {
    digitalWrite(i, HIGH);
    delay(1000);
    digitalWrite(i, LOW);
    delay(1000);
  }
}
