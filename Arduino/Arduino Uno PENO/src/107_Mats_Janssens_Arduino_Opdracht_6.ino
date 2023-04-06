// Zesde opdracht

int analog_pin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(analog_pin, INPUT);
}

void loop() {
    if (Serial.available()) {
        Serial.println("type v for volt read:");
        char userinput =  Serial.read();

        // We doen maal 5 en delen door 1024
        // Omdat de analogread het voltage mapt tussen 
        // 0 en 1023
        int analog = analogRead(analog_pin)/1024*5;
        if (userinput == 'v') {
            Serial.print(analog);
        }
    }
}

