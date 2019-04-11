// MazeSolver

  //Initialize Pins
    // H-Bridge Pins
int ena = 3;
int in4 = 2;
int in3 = 4;
int in1 = 5;
int in2 = 7;
int enb = 6;

    // RangeFinder Pins
int echoF = 8;
int triggerF = 9;
int echoR = 10;  
int triggerR = 11;
int echoL = 12;
int triggerL = 13;

// Constants
int OBSTACLE_CLOSE = -1;  // Determines how close to a wall the robot must get before turning. May be adjusted
#define LEFT 3
#define RIGHT 2
#define STRAIGHT 1
#define WAIT_TIME 290           // Time between commands.
#define STRAIGHT_TIME 50      // How long to go straight
#define LEFT_TURN_TIME  345     // How long for left turn
#define RIGHT_TURN_TIME 270     // How long for right turn
#define LEFT_SPEED 145
#define RIGHT_SPEED 237

// Initialize variables
float straightDistance = 0, rightDistance = 0, leftDistance = 0;

void setup() {
      // Sets the pins as input pins or output pins, according to role
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(triggerF, OUTPUT);
  pinMode(echoF, INPUT);
  pinMode(triggerR, OUTPUT);
  pinMode(echoR, INPUT);
  pinMode(triggerL, OUTPUT);
  pinMode(echoL, INPUT);
  Serial.begin(9600);        // Sets the baud rate
  delay(1000);
}

// Will work, but doesn't actually guarantee a solved maze as it is right now
void loop() {
  /*while (GetDistance(STRAIGHT) > OBSTACLE_CLOSE) {
    GoStraight();
  } */
  
  straightDistance = GetDistance(STRAIGHT);
  rightDistance = GetDistance(RIGHT);
  leftDistance = GetDistance(LEFT);
  GoStraight();

  if (straightDistance < OBSTACLE_CLOSE){
//  if (leftDistance < OBSTACLE_CLOSE && rightDistance < OBSTACLE_CLOSE) {
//      LeftTurn90();
//      LeftTurn90();
//    }
    if (leftDistance > rightDistance) {
      LeftTurn90();
    }
    else if (rightDistance > leftDistance) {
      RightTurn90();
    }
  }
  OBSTACLE_CLOSE = 12;
}

void GoStraight() {
  
  // Sets all wheels to forward     -    these may need to be changed
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(ena, LEFT_SPEED);
    analogWrite(enb, RIGHT_SPEED);

  
  //For testing
  //delay(STRAIGHT_TIME);

  

  return;
}

void Pause() {
  
    // Sets Left wheel to forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, 0);
    // Left Right is turned BACKWARD
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, 0);
  
  delay(WAIT_TIME);
  
  return;
}

void RightTurn90() {
  Pause();
  
    // Sets Left wheel to forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, LEFT_SPEED);
    // Left Right is turned BACKWARD
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, RIGHT_SPEED);
    // Continues for enough time to turn 90 degrees. TURN_TIME (top of file) will need to be adjusted 
  delay(RIGHT_TURN_TIME);   

  Pause();
  
  return;
}

void LeftTurn90() {
  Pause();
  
    // Left wheel is turned off
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, LEFT_SPEED);
    // Sets Right wheel to forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, RIGHT_SPEED);
    // Continues for enough time to turn 90 degrees. TURN_TIME (top of file) will need to be adjusted
  delay(LEFT_TURN_TIME);
  return;
  
  Pause();
}

double GetDistance(int directions) {
  double duration, distance;

  if (directions == STRAIGHT) {
      // Sequence to activate the rangeFinders and read the data
    digitalWrite(triggerF, LOW);

    delayMicroseconds(2);
    digitalWrite(triggerF, HIGH);

    delayMicroseconds(10);
    duration = pulseIn(echoF, HIGH);
    distance = (duration / 2) * 0.0343; // Converts from m/s to cm/us

    //Serial.println("distance1 =  ");
    //Serial.println(distance);
  } else if (directions == RIGHT) {
      // Sequence to activate the rangeFinders and read the data
    digitalWrite(triggerR, LOW);

    delayMicroseconds(2);
    digitalWrite(triggerR, HIGH);

    delayMicroseconds(10);
    duration = pulseIn(echoR, HIGH);
    distance = (duration / 2) * 0.0343; // Converts from m/s to cm/us

    //Serial.println("distance2 =  ");
    //Serial.println(distance);
  } else if (directions == LEFT) {
      // Sequence to activate the rangeFinders and read the data
    digitalWrite(triggerL, LOW);

    delayMicroseconds(3);
    digitalWrite(triggerL, HIGH);

    delayMicroseconds(10);
    duration = pulseIn(echoL, HIGH);
    distance = (duration / 2) * 0.0343; // Converts from m/s to cm/us

    // Serial.println("distance3 =  ");
    //Serial.println(distance);
  }
  return distance;

}
