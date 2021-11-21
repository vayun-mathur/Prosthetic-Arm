#include <Servo.h>

struct finger {
  Servo servo;
  int max_angle;
  void init(int pin, int max_angle) {
    servo.attach(pin);
    this->max_angle = max_angle;
  }
  void write(double angle) {
    servo.write((int)(angle*max_angle));
  }
};

finger thumb, index, middle, ring, pinky;

Servo wrist;
