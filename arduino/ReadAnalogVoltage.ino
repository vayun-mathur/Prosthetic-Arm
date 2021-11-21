#include "finger.h"
#include "sensor.h"
#include <Servo.h>

// Define the pins
#define thumbPin 12
#define indexPin 11
#define middlePin 10
#define ringPin 9
#define pinkyPin 8
#define wristPin 13

void initCheckData();

sensor s1; //green
sensor s2; //black
sensor s3; //red

void setup() {
  thumb.init(thumbPin, 90);
  index.init(indexPin, 140);
  middle.init(middlePin, 140);
  ring.init(ringPin, 140);
  pinky.init(pinkyPin, 130);
  wrist.attach(wristPin);
  Serial.begin(9600);
  s1.attach(A1); //green
  s2.attach(A2); //black
  s3.attach(A3); //red
  //initCheckData();
}



double* hand_closed = new double[6] {0.26, 0.14, 0.12, 0.87, 0.67, 0.96};
double* extend_thumb = new double[6] {15.8, 3.67, 2.5, 4.7, 1.7, 1.83};
double* keep_thumb = new double[6] {0.32, 0.18, 0.18, 0.9, 0.6, 0.96};
double* extend_index = new double[6] {7.38, 8.3, 6.68, 3.29, 2.83, 2.55};
double* keep_index = new double[6] {0.2, 0.33, 0.26, 0.81, 0.81, 1.0};
double* extend_pinky = new double[6] {4.96, 5.11, 17.48, 2.25, 2.31, 4.76};
double* keep_pinky = new double[6] {0.41, 0.17, 1.2, 0.97, 0.65, 1.37};
double* extend_thumb_index = new double[6] {18.05, 7.15, 5.62, 4.71, 2.75, 2.68};
double* keep_thumb_index = new double[6] {0.76, 0.48, 0.33, 1.1, 0.69, 1.14};
double* extend_thumb_pinky = new double[6] {14.79, 4.9, 16.11, 4.7, 2.26, 4.76};
double* keep_thumb_pinky = new double[6] {0.48, 0.32, 1.22, 1.11, 0.7, 1.57};
double* extend_index_pinky = new double[6] {4.42, 3.84, 15.47, 2.18, 1.63, 4.76};
double* keep_index_pinky = new double[6] {0.49, 0.43, 1.16, 0.98, 0.88, 1.7};
double* extend_thumb_index_pinky = new double[6] {16.18, 5.83, 13.89, 4.7, 2.49, 4.75};
double* keep_thumb_index_pinky = new double[6] {0.61, 0.41, 0.87, 1.09, 0.87, 1.53};

double** extensions = new double*[8];
double** keeps = new double*[8];

void initCheckData() {
  //thumb, index, pinky
  extensions[0b000] = new double[6]{0,0,0,0,0,0};
  extensions[0b001] = extend_pinky;
  extensions[0b010] = extend_index;
  extensions[0b011] = extend_index_pinky;
  extensions[0b100] = extend_thumb;
  extensions[0b101] = extend_thumb_pinky;
  extensions[0b110] = extend_thumb_index;
  extensions[0b111] = extend_thumb_index_pinky;

  keeps[0b000] = hand_closed;
  keeps[0b001] = keep_pinky;
  keeps[0b010] = keep_index;
  keeps[0b011] = keep_index_pinky;
  keeps[0b100] = keep_thumb;
  keeps[0b101] = keep_thumb_pinky;
  keeps[0b110] = keep_thumb_index;
  keeps[0b111] = keep_thumb_index_pinky;
}

double* data = new double[6];

double distance(double* data2) {
  double d = 0;
  for(int i=0;i<6;i++) {
    d += abs(data[i] - data2[i]);
  }
  return d;
}

//zero means closed
int currentState = 0b000;



// the loop routine runs over and over again forever:
void loop() {
  double fluc1 = s1.update();
  double fluc2 = s2.update();
  double fluc3 = s3.update();
  double val1 = s1.mx();
  double val2 = s2.mx();
  double val3 = s3.mx();
  /*
  
  data[0] = fluc1, data[1] = fluc2, data[2] = fluc3;
  data[3] = val1, data[4] = val2, data[5] = val3;

  double closestDist = 10000;
  int closestState = -1;
  bool isExtension = false;
  for(int i=1;i<(1<<3);i++) {
    double* stateToCheck = keeps[i];
    bool works = true;
    for(int j=1;j<(1<<3);j*=2) {
      if((currentState & j == 0) && (i & j == j)) {
        works = false;
        break;
      }
    }
    if(!works) continue;
    if(distance(stateToCheck) < closestDist) {
      closestDist = distance(stateToCheck);
      closestState = i;
    }
  }
  int x;
  for(int i=1;i<(1<<3);i++) {
    double* stateToCheck = extensions[i];
    bool works = true;
    for(int j=1;j<(1<<3);j*=2) {
      
      if((currentState & j == j) && (i & j == j)) {
        works = false;
        break;
      }
      
    }
    //if(!works) continue;
    if(distance(stateToCheck) < closestDist) {
      closestDist = distance(stateToCheck);
      closestState = i + currentState;
      isExtension = true;
      if(!works) {
        closestState = -1;
      }
      x = i;
    }
  }
  if(closestState != -1) {
    currentState = closestState;
  
    if(isExtension) {
      Serial.print((x&4) / 4);
      Serial.print((x&2) / 2);
      Serial.print((x&1) / 1);
      Serial.println();
    }
  }

  bool thumbO = (currentState&4) == 4;
  bool indexO = (currentState&2) == 2;
  bool pinkyO = (currentState&1) == 1;
  
  

  */
  Serial.print(val1);
  Serial.print(' ');
  Serial.print(val2);
  //Serial.print(' ');
  //Serial.print(val3);
  Serial.println();

  double t1 = 4.5;
  double t2 = 4.5;

  bool thumbO = val1 > t1;
  bool indexO = val2 > t2;
  bool pinkyO = val2 > t2;
  
  
  thumb.write(thumbO?0:1);
  index.write(indexO?0:1);
  middle.write(indexO?0:1);
  ring.write(pinkyO?0:1);
  pinky.write(pinkyO?0:1);
  
  delay(10);
}
