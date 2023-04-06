// Negende opdracht

int analog_pin = A0;
int led_pin = 5;

void setup() {
  Serial.begin(9600);
  pinMode(analog_pin, INPUT);
  pinMode(led_pin, OUTPUT);
}

void loop() {
    char userinput =  Serial.read();
    Serial.println("type v for volt read:");

    // We doen maal 5 en delen door 1024
    // Omdat de analogread het voltage mapt tussen 
    // 0 en 1023
    int analog = analogRead(analog_pin)/1024*5;

    if (userinput == 'v') {
        Serial.print(analog);
    }

    gradient_led(analog);

}

void gradient_led( int analog) {
    if (analog > 2.5){
        for (float volt=0; volt<5; volt = volt + 0.1) {
            // opdelen in 50 stapjes
            analogWrite(led_pin,255*volt/50);
            delay(50);
        } 
    }

    int analog = analogRead(analog_pin)/1024*5;
    // Als het licht terug aan is na de loop gaan we 
    // Het lampje terug beginnen dimmen
    dim_led(analog);
}

void dim_led(int analog) {
    if (analog < 2.5) {
        for (float volt=5; volt>0; volt = volt - 0.1) {
            // opdelen in 50 stapjes
            analogWrite(led_pin,255*volt/50);
            delay(50);
        }
    }
}

