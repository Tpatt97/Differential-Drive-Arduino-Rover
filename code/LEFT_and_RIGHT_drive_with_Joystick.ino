//Including Libraries//
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//OLED Definitions//
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// Establishment of Variables //
int xValue;
int yValue;

int throttle;
int steering;

int leftMotorSpeed;
int rightMotorSpeed;

int leftMotorPin = 5;
int rightMotorPin = 6;


void setup() {

  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);

  Serial.begin(9600);

  //OLED SETUP//
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    for(;;);
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,0);
  display.println("ROVER ONLINE");

  display.display();

  delay(2000);

}

void loop() {
  // Read Joystick //
  xValue = analogRead(A0);
  yValue = analogRead(A1);

  // Convert Joystick values //
  throttle = map(yValue, 0, 1023, -255, 255);
  steering = map(xValue, 0, 1023, -255, 255);

  // Deadzone //
  if (abs(throttle) < 20) {
    throttle = 0;
  }

  if (abs(steering) < 20) {
    steering = 0;
  }

  // Differential steering math //
  leftMotorSpeed = throttle + steering;
  rightMotorSpeed = throttle - steering;

  // Constrain values //
  leftMotorSpeed = constrain(leftMotorSpeed, 0, 255);
  rightMotorSpeed = constrain(rightMotorSpeed, 0, 255);

  // Output PWM //
  analogWrite(leftMotorPin, leftMotorSpeed);
  analogWrite(rightMotorPin, rightMotorSpeed);

  // Debug //
  Serial.print("Throttle: ");
  Serial.print(throttle);

  Serial.print("  Steering: ");
  Serial.print(steering);

  Serial.print("  Left: ");
  Serial.print(leftMotorSpeed);

  Serial.print("  Right: ");
  Serial.println(rightMotorSpeed);


  // OLED Telemetry //
  int throttlePercent = map(abs(throttle), 0, 255, 0, 100);
  int biasPercent = map(steering, -255, 255, -100, 100);
  int leftPercent = map(leftMotorSpeed, 0, 255, 0, 100);
  int rightPercent = map(rightMotorSpeed, 0, 255, 0, 100);

  display.clearDisplay();
  display.setCursor(0,0);

  display.print("THRTL: ");
  display.print(throttlePercent);
  display.println("%");

  display.print("BIAS: ");
  display.print(biasPercent);
  display.println("%");

  display.println();

  display.print("L: ");
  display.print(leftPercent);
  display.println("%");

  display.print("R: ");
  display.print(rightPercent);
  display.println("%");

  display.display();



  delay(200);
}


