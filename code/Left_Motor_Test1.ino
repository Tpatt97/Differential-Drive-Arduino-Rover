int yValue;
int motorSpeed;

int motorPin = 5;

void setup() {

  pinMode(motorPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  yValue = analogRead(A1);

  //Map joystick range to PWM range
  motorSpeed = map(yValue, 512, 1023, 0 , 255);

  //Prevent negative values
  if (motorSpeed < 0) {
    motorSpeed = 0;
  }

  analogWrite(motorPin, motorSpeed);

  Serial.print("Y: ");
  Serial.print(yValue);

  Serial.print("PWM: ");
  Serial.println(motorSpeed);

  delay(50);

}
