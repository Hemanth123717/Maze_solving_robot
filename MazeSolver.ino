
const int trigPinFront = 8;
const int echoPinFront = 7;
const int trigPinLeft = 10;
const int echoPinLeft = 9;
const int trigPinRight = 6;
const int echoPinRight = 5;

// Motor control pins
const int motor1Pin1 = 28;
const int motor1Pin2 = 29;
const int motor2Pin1 = 26;
const int motor2Pin2 = 27;
 
int ena=23,enb = 25;

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);

  // Motor pins setup
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);

  digitalWrite(ena,HIGH);
  digitalWrite(enb,HIGH);
}

float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2; // Speed of sound is 0.034 cm/microsecond
  return distance;
}

void moveForward() {
  float leftDistance = getDistance(trigPinLeft, echoPinLeft);
  float rightDistance = getDistance(trigPinRight, echoPinRight);
  if(rightDistance <8 && leftDistance >10){
    turnLeft();
    delay(75);
    stopMotors();
    delay(50);
    // Serial1.print("Front Distance: ");
    // Serial1.print(frontDistance);
    Serial1.print(" cm, Left Distance: ");
    Serial1.print(leftDistance);
    Serial1.print(" cm, Right Distance: ");
    Serial1.print(rightDistance);
    Serial1.println(" cm");
  }
  else if(leftDistance <8 && rightDistance >10){
    turnRight();
    delay(75);
    stopMotors();
    delay(50);
    Serial1.print(" cm, Left Distance: ");
    Serial1.print(leftDistance);
    Serial1.print(" cm, Right Distance: ");
    Serial1.print(rightDistance);
    Serial1.println(" cm");
  }else {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    // Serial1.print("Front Distance: ");
    // Serial1.print(frontDistance);
    Serial1.print(" cm, Left Distance: ");
    Serial1.print(leftDistance);
    Serial1.print(" cm, Right Distance: ");
    Serial1.print(rightDistance);
    Serial1.println(" cm");
  }
} 


void turnRight() {
  // analogWrite(ena, 150);
  // analogWrite(enb, 150);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void turnLeft() {
  // analogWrite(ena, 150);
  // analogWrite(enb, 150);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void loop() {
  float frontDistance = getDistance(trigPinFront, echoPinFront);
  float leftDistance = getDistance(trigPinLeft, echoPinLeft);
  float rightDistance = getDistance(trigPinRight, echoPinRight);

  Serial.print("Front Distance: ");
  Serial.print(frontDistance);
  Serial.print(" cm, Left Distance: ");
  Serial.print(leftDistance);
  Serial.print(" cm, Right Distance: ");
  Serial.print(rightDistance);
  Serial.println(" cm");
  
  if (leftDistance > 10 && frontDistance < 15){
    turnLeft();
    delay(250);
    stopMotors();
    delay(500);
  }else if(rightDistance > 10 && frontDistance < 15){
    turnRight();
    delay(250);
    stopMotors();
    delay(500);
    // delay(15);
  }else{
    moveForward();
    delay(400);
    stopMotors();
    delay(500);
    // delay(15);
  }
}
