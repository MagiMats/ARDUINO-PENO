// Achtste opdracht

int analog_pin = A0;
int led_pin = 5;

void setup() {
  Serial.begin(9600);
  pinMode(analog_pin, INPUT);
  pinMode(led_pin, OUTPUT);
}

void loop() {
    // We doen maal 5 en delen door 1024
    // Omdat de analogread het voltage mapt tussen 
    // 0 en 1023
    int analog = analogRead(analog_pin)/1024*5;
    Serial.print(analog);

    led_checker(analog);

}

void led_checker( int analog) {
    if (analog > 2.5){
        digitalWrite(led_pin, HIGH);
    }
    else {
        digitalWrite(led_pin, LOW);
    }
}


