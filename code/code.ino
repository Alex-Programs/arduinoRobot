void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  bool found = searchcycle();

  if (found) {
    home();
  }
}

bool searchcycle() {
  // Spiral pattern
  rotate_motors(20, 40);
  float distance = find_distance();
  return distance > 10;
}

void home() {
  // We've found something, now we're going to home in. Once we're < 5cm we stay there till it disappears, then exit.
  int forwardAmount = 0;

  while (true) {
      rotate_motors(30, 30);
      forwardAmount = forwardAmount + 1;
      
      float distance = find_distance();
      if (distance > 10) {
        // We've lost it before the 5cm mark. TODO make this go left/right trying to find it.
      }
      if (distance < 5) {
        // We've found it. Stay here until it disappears.
        while (distance < 5.5) {
           float distance = find_distance();
           // TODO Flash LED
        }
        // Now it's gone. Return back
        break;
      }
  }

  // TODO go back to start pos and rot. Takes tuning so not doing now.
}

// Nice funcs: pinMode(pin, type) - input or output
// digitalWrite(pin, value) - write to selected pin. EIther high or low (voltage)
// delay(time)


// Motor control
const int motorA_pin1 = 5;
const int motorA_pin2 = 6;

const int motorB_pin1 = 9;
const int motorB_pin2 = 10;

// 0-255 range
void rotate_motors(int left, int right) {
  analogWrite(motorA_pin1, left);
  analogWrite(motorB_pin1, right);
}

// Ultrasonic in centimetres
#define ECHO_PIN 2
#define TRIG_PIN 3

float find_distance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration / 58.2;
  delayMicroseconds(10);

  return distance;
}
