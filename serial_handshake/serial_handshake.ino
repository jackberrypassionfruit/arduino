int buffer;
String message; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    message = "";

    buffer = Serial.read(); // read the incoming byte:
    while (buffer > 10) { // ord('\r') is 10
      message += char(buffer);
      buffer = Serial.read();
    }
    
    Serial.print("I received: ");
    Serial.print(message);
    Serial.println(", Bitch");
  }
}
