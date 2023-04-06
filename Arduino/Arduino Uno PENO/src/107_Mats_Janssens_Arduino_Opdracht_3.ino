// Derde Opdracht

void setup() {
  init_led_loop();
}

void loop() {
  led_loop();
}


void init_led_loop () {
  for (int i = 2; i<=8; i=i+1) {
    pinMode(i, OUTPUT);
  }
}

void led_loop() {
    if (Serial.available()) {
        Serial.println("Enter the pin of the led");
        int led_choice = Serial.read();
        int led_choice_spec = led_choice - 1;

        Serial.println("Enter the duration");
        int duration_choice = Serial.read();

        // Checken of de leds wel een poort hebben
        if (led_choice_spec < 7 && led_choice_spec > 0) {

            // Nog eens checken of de tijd geen negatief getal is
            if (duration_choice < 0) {
                Serial.println("Enter a positive integer");
            }
            digitalWrite(led_choice_spec, HIGH);
            delay(duration_choice);
            digitalWrite(led_choice_spec, LOW);
        }
    }
}