#include <LinkedList.h>

double voltage(int pin) {
  return analogRead(pin) * (5.0 / 1023.0);
}

struct sensor {
  int pin;
  LinkedList<double> v;

  void attach(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
  }

  double getLast() {
    return v.get(v.size()-1);
  }

  double mx() {
    double m = 0;
    for(int i=0;i<v.size();i++){
      m = max(m, v.get(i));
    }
    return m;
  }

  double update() {
    v.add(voltage(pin));
    if(v.size()>50) {
      v.remove(0);
    }
    double avg = 0;
    for(int i=0;i<v.size();i++) {
      avg += v.get(i);
    }
    avg /= v.size();
    double f = 0;
    for(int i=0;i<v.size();i++) {
      f += abs(v.get(i)-avg);
    }
    f /= v.size();
    f *= 10;
    return f;
  }
};
