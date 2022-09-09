#define ECHO_PIN 2
#define TRIG_PIN 3

void setup() {
  // put your setup code here, to run once:
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //while (true) {
  //  float distance = find_distance();
  //    showNum(distance);
  //}
  
  bool found = searchcycle();

  if (found) {
    home();
  }
}

bool searchcycle() {
  // Spin
  rotate_motors(0, 255);
  rotate_motors_backward(255, 0);
  float distance = find_distance();
  return distance < 30;
}

void debug() {
        int i = 0;
        while (i < 10) {
          digitalWrite(13, HIGH);
          delay(100);
          digitalWrite(13, LOW);
          delay(100);

          i = i + 1;
        }
}

void showNum(float inputNum) {
  if (inputNum > 1000) {
    digitalWrite(13, LOW);
    return;
  }
          digitalWrite(13, HIGH);
          delay(inputNum);
          digitalWrite(13, LOW);
          delay(inputNum);
}

void home() {
  // We've found something, now we're going to home in. Once we're < 5cm we stay there till it disappears, then exit.
  int forwardAmount = 0;
  float timeOn = 0;
  float startTime = millis();

  while (true) {
      rotate_motors(200, 200);
      forwardAmount = forwardAmount + 1;
      
      float distance = find_distance();

      if (distance > 30) {
        rotate_motors(0, 0);
        rotate_motors_backward(0, 0);

        //debug();
        
        timeOn = timeOn + (millis() - startTime);
        startTime = millis();
        // We've lost it before the 5cm mark. TODO make this go left/right trying to find it.
      }
      if (distance < 5) {
        rotate_motors(0, 0);
        rotate_motors_backward(0, 0);

        timeOn = timeOn + (millis() - startTime);

        digitalWrite(13, HIGH);
        // We've found it. Stay here until it disappears.
        while (find_distance() < 5.5) {
           delay(10);
        }

        digitalWrite(13, LOW);
        // Now it's gone. Return back
        break;
      }
  }

  // timeOn is how long we need to run it backwards
  float startReturnTime = millis();
  while (millis() - startReturnTime < timeOn) {
    rotate_motors_backward(200, 200);
  }
}

// Nice funcs: pinMode(pin, type) - input or output
// digitalWrite(pin, value) - write to selected pin. Either high or low (voltage)
// delay(time)


// Motor control
const int motorA_pin1 = 5;
const int motorA_pin2 = 6;

const int motorB_pin1 = 9;
const int motorB_pin2 = 10;

// 0-255 range
void rotate_motors_backward(int left, int right) {
  analogWrite(motorA_pin1, left);
  analogWrite(motorB_pin1, right);
}

void rotate_motors(int left, int right) {
  analogWrite(motorA_pin2, left);
  analogWrite(motorB_pin2, right);
}

// Ultrasonic in centimetres. yes it returns a float as an int? IDK C
int find_distance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration / 58.2;
  delayMicroseconds(10);
  //int dist_int = distance.

  return distance;
}
