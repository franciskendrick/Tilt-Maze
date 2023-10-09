#include <Servo.h> 
 
//  Create servo objects to control the servos
Servo servo_x; 
Servo servo_y;
 
// Analog pins to connect the joystick
#define VRx_pin  A0 // Arduino pin connected to VRX pin
#define VRy_pin  A1 // Arduino pin connected to VRY pin

// Digital pins to connect button
#define go_pin  2

// Variables to read the x and y value from the analog pins
int x_val = 0;
int y_val = 0;

// Buttons
int go_btnstate = 0;
int timergo = false;

// LED pins
int LED_green = 13;
int LED_yellow = 12;
int LED_red = 11;
int LED_sec = 10;
int sec_counter = 0;

void update_servo(int range)
{
  for (int i = 0; i <= range; i++) {
      // Get scaled value
      x_val = map(analogRead(VRx_pin), 0, 1023, 0, 20);
      y_val = map(analogRead(VRy_pin), 0, 1023, 0, 20);

      // Set the servo position accroding to the scaled value
      servo_x.write(x_val);
      servo_y.write(y_val);

      delay(50);

      // Serial plotter
      Serial.print("x = ");
      Serial.print(x_val);
      Serial.print(": y = ");
      Serial.print(y_val);
      Serial.print(": go_val = ");
      Serial.print(go_btnstate);
      Serial.print(": counter = ");
      Serial.println(sec_counter);
    }
}
 
void setup() 
{ 
  Serial.begin(9600); 
  servo_x.attach(9);  // attaches the x servo on pin 9 to the servo object 
  servo_y.attach(8);  // attaches the y servo on pin 8 to the servo object 

  pinMode(go_pin, INPUT);
  pinMode(LED_green, OUTPUT);
  pinMode(LED_yellow, OUTPUT);
  pinMode(LED_red, OUTPUT);

  digitalWrite(go_pin, HIGH);
} 
 
void loop() 
{ 
  go_btnstate = digitalRead(go_pin);

  update_servo(1);

  if (go_btnstate == HIGH && timergo == false) {
    timergo = true;

    digitalWrite(LED_green, HIGH);
    digitalWrite(LED_yellow, HIGH);
    digitalWrite(LED_red, HIGH);
  }

  if (timergo == true) {
    digitalWrite(LED_sec, HIGH);
    update_servo(5);

    digitalWrite(LED_sec, LOW);
    update_servo(15);

    sec_counter += 1;
    if (sec_counter == 10) {
      digitalWrite(LED_green, LOW);
    }
    else if (sec_counter == 20) {
      digitalWrite(LED_yellow, LOW);
    }
    else if (sec_counter == 30) {
      digitalWrite(LED_red, LOW);
      timergo = false;
    }
  }
} 
