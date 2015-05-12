#include <AFMotor.h>
AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
int sensorC = A0;
int cmSensorC;
int sensorR = A1;
int cmSensorR;
int sensorL = A2;
int cmSensorL;
bool bored = 0;
int minDistance = 20;
void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  motor1.setSpeed(150); // set the speed to 200/255
  motor2.setSpeed(150); // set the speed to 200/255
}
void loop() {
  readSensorC();
  readSensorL();
  readSensorR();
  if (isBored()) {
    Serial.println("Im bored...");
  } else {
    Serial.println("Im doing something...");
    if (hasWall()) {
      Serial.println("There's a wall infront of me");
      backward(1);
      turnLeft(90);
    }else{
    forward(1);
    }
  }
}
bool hasWall() {
  if ((cmSensorC < 15) && (cmSensorL < 20) && (cmSensorR < 20)) {
    return true;
  } else {
    return false;
  }
}
bool isBored() {
  if (cmSensorC > 50 && cmSensorL > 50 && cmSensorR > 50) {
    return true;
  } else {
    return false; 
  }
}
bool centerTooClose() {
  if (cmSensorC < 30) {
    return true;
  } else {
    return false;
  }
}
bool leftIsCloser() {
  if (cmSensorL < cmSensorC && cmSensorL < cmSensorR && cmSensorL > minDistance && cmSensorL < 100) {
    return true;
  } else {
    return false;
  }
}

bool rightIsCloser() {
  if (cmSensorR < cmSensorC && cmSensorR < cmSensorL && cmSensorR > minDistance && cmSensorR < 100) {
    return true;
  } else {
    return false;
  }
}

bool centerIsCloser() {
  if (cmSensorC < cmSensorL && cmSensorC < cmSensorR && cmSensorC > minDistance && cmSensorC < 100) {
    return true;
  } else {
    return false;
  }
}
void forward(int distance) {
  int segundosFinal;
  Serial.println("Going forward ");
  //if (distance <= 0) {
    //Serial.print(distance);
    //Serial.print(" cms");
    //segundosFinal = 0;
  //} else {
   // Serial.print(distance);
    //Serial.print(" centimeters\n");
    //int segundos = (distance * 1000) / 60;
    //segundosFinal = segundos;
  //}
  motor1.run(BACKWARD); // turn it on going forward
  motor2.run(BACKWARD); // turn it on going forward
  delay(distance);
  stop();
}
void backward(int distance) {
  Serial.print("Going backward ");
  Serial.print(distance);
  Serial.print(" centimeters\n");
  int segundos = (distance * 1000) / 60;
  motor1.run(FORWARD); // the other way
  motor2.run(FORWARD); // the other way
  delay(distance);
  stop();
}
void stop() {
  motor1.run(RELEASE); // stopped
  motor2.run(RELEASE); // stopped
}
void turnRight(double grados) {
  Serial.print("Turning right ");
  Serial.print(grados);
  Serial.print(" degrees\n");
  double segundos = (grados * 2000) / 270;
  motor1.run(FORWARD); // turn it on going forward
  motor2.run(BACKWARD); // turn it on going forward
  delay(segundos);
  stop();
}
void turnLeft(double grados) {
  Serial.print("Turning left ");
  Serial.print(grados);
  Serial.print("degrees\n");
  double segundos = (grados * 2000) / 270;
  motor1.run(BACKWARD); // turn it on going forward
  motor2.run(FORWARD); // turn it on going forward
  delay(segundos);
  stop();
}
void readSensorC() {
  int lectura;
  lectura = analogRead(sensorC);
  cmSensorC = pow(3027.4 / lectura, 1.2134);
  Serial.print("Center Sensor: ");
  Serial.print(cmSensorC);
  Serial.print("\n");
  delay(500);
}
void readSensorL() {
  int lectura;
  lectura = analogRead(sensorL);
  cmSensorL = pow(3027.4 / lectura, 1.2134);
  Serial.print("Left sensor: ");
  Serial.print(cmSensorL);
  Serial.print("\n");
  delay(500);
}
void readSensorR() {
  int lectura;
  lectura = analogRead(sensorR);
  cmSensorR = pow(3027.4 / lectura, 1.2134);
  Serial.print("Right sensor: ");
  Serial.print(cmSensorR);
  Serial.print("\n");
  delay(500);
}


