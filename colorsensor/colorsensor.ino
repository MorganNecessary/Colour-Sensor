// Define color sensor pins
#define S0 4
#define S1 5
#define S2 8
#define S3 7
#define sensorOut 9
#define oepin 6

// Calibration Values
// *Get these from Calibration Sketch
int redMin = 30; // Red minimum value
int redMax = 180; // Red maximum value
int greenMin = 50; // Green minimum value
int greenMax = 200; // Green maximum value
int blueMin = 30; // Blue minimum value
int blueMax = 190; // Blue maximum value

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variables for final Color values
int redValue;
int greenValue;
int blueValue;

String sentence;

void setup() {
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(oepin, OUTPUT);

  // Set Sensor output as input
  pinMode(sensorOut, INPUT);

  // Set Frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  digitalWrite(oepin, LOW);

  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Read Red value
  redPW = getRedPW();
  // Map to value from 0-255
  redValue = map(redPW, redMin,redMax,255,0);
  // Delay to stabilize sensor
  delay(200);

  // Read Green value
  greenPW = getGreenPW();
  // Map to value from 0-255
  greenValue = map(greenPW, greenMin,greenMax,255,0);
  // Delay to stabilize sensor
  delay(200);

  // Read Blue value
  bluePW = getBluePW();
  // Map to value from 0-255
  blueValue = map(bluePW, blueMin,blueMax,255,0);
  // Delay to stabilize sensor
  delay(200);

  //is red the greatest value?
  if(redValue > blueValue && redValue > greenValue && redValue > 100){
    sentence = "the color is red";
  }

  //is blue the greatest value?
  if(blueValue > redValue && blueValue > greenValue && blueValue > 100){
    sentence = "the color is blue";
  }  
  
  //is green the greatest value?
  if(greenValue > redValue && greenValue > blueValue && greenValue > 100){
    sentence = "the color is green";
  }    

  //is red green and blue each less than 50?
  if(redValue < 50 && greenValue < 50 && blueValue < 50){
    sentence = "the color is black";
  }    


  
  
  
  // Print output to Serial Monitor
  Serial.println(sentence);
  sentence = "";
}


// Function to read Red Pulse Widths
int getRedPW() {
  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}
