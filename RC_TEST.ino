int pin1 = 22; //REPLACE 22 WITH YOUR RUDD/AIL pin
int pin2 = 30; //REPLACE 30 WITH YOUR THROTTLE pin

void setup() {
 Serial.begin(9600);
 pinMode(pin1, INPUT);
 pinMode(pin2, INPUT);

}

void loop() {
 int speedValue = pulseIn(pin1, HIGH);
  int directionValue = pulseIn(pin2, HIGH);
  
  //Serial.println(speedValue);
  Serial.println(directionValue);

  delay(50);

}

