// ---------------- SENSOR PINS ----------------

#define LM35 A0
#define MQ2 A1

#define PIR_FRONT 7
#define PIR_BACK 8

#define IR_SENSOR 6

#define TRIG 9
#define ECHO 10

// Color sensor
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 11

// ---------------- MOTOR DRIVER ----------------

#define IN1 A2
#define IN2 A3
#define IN3 A4
#define IN4 A5

// ---------------- THRESHOLDS ----------------

#define TEMP_THRESHOLD 90
#define GAS_THRESHOLD 400
#define OBSTACLE_DISTANCE 20

// ---------------- VARIABLES ----------------

int redValue;
int greenValue;
int blueValue;

bool missionStarted = false;
bool returnMode = false;

// ---------------- SETUP ----------------

void setup(){

  Serial.begin(9600);

  pinMode(PIR_FRONT, INPUT);
  pinMode(PIR_BACK, INPUT);
  pinMode(IR_SENSOR, INPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.println("ROLEX robot ready");
}

// ---------------- LOOP ----------------

void loop(){

  // ---------------- WAIT FOR ENTRY COLOR ----------------

  if(!missionStarted){

    Serial.println("Searching entry color...");

    if(isBlueDetected())
    {
      Serial.println("Entry color detected");
      missionStarted = true;

      delay(1000);
    }

    delay(1000);
    return;
  }

  // ---------------- RETURN MODE ----------------

  if(returnMode){

    Serial.println("Searching entry color...");

    if(isBlueDetected()){

      Serial.println("Entry color found");
      Serial.println("Exiting mission");

      stopRobot();

      while(true);
    }

    turnRight();
    delay(400);

    return;
  }

  // ---------------- SENSOR READINGS ----------------

  float temperature = readTemperature();
  int gas = readGas();
  float distance = readDistance();

  Serial.print("Temperature: ");
  Serial.println(temperature);

  Serial.print("Gas: ");
  Serial.println(gas);

  Serial.print("Distance: ");
  Serial.println(distance);

  // ---------------- HUMAN DETECTION ----------------

  if(digitalRead(PIR_FRONT)==HIGH){

    Serial.println("Motion detected in FRONT");
  }

  if(digitalRead(PIR_BACK)==HIGH){

    Serial.println("Motion detected in BACK");
  }

  // ---------------- CLIFF DETECTION ----------------

  if(digitalRead(IR_SENSOR)==HIGH){

    Serial.println("Cliff detected");
  }

  // ---------------- HAZARD DETECTION ----------------

  if(temperature > TEMP_THRESHOLD || gas > GAS_THRESHOLD){

    Serial.println("Hazard detected");

    stopRobot();

    returnMode = true;

    delay(1000);

    return;
  }

  // ---------------- OBSTACLE AVOIDANCE ----------------

if(distance > 0 && distance < OBSTACLE_DISTANCE){

    Serial.println("Obstacle detected");

    stopRobot();
    delay(500);

    turnRight();
    delay(400);

    stopRobot();
    delay(200);
}
}

// ---------------- SENSOR FUNCTIONS ----------------

float readTemperature(){

  int value = analogRead(LM35);
  float voltage = value * (5.0 / 1023.0);
  float temp = voltage * 100;

  return temp;
}

int readGas(){

  int gasValue = analogRead(MQ2);

  return gasValue;
}

float readDistance(){

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);

  float distance = duration * 0.034 / 2;

  return distance;
}

// ---------------- COLOR SENSOR ----------------

void readColor(){

  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redValue = pulseIn(sensorOut, LOW);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenValue = pulseIn(sensorOut, LOW);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueValue = pulseIn(sensorOut, LOW);
}

bool isBlueDetected(){

  readColor();

  if(blueValue < redValue && blueValue < greenValue){
    return true;
  }

  return false;
}

// ---------------- MOTOR FUNCTIONS ----------------

void moveForward(){

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight(){

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopRobot(){

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
} 
