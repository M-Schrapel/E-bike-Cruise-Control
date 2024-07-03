/************************************************************************
*
*       Basic example of a Cruise Control technology for e-bikes
*       By Maximilian Schrapel
*
*
************************************************************************/

// Set your wheel circumference!
double wheelsz      =  2.033; // wheel circumference in meters
double maxSpeed_kmh = 22.0;   // Your desired speed limit in km/h

unsigned long wheel = 0;    // internal wheel parameter for speed calculation
double        speed = 0.0;  // Current speed      

unsigned long maxSpeedTime  = 10000000; // Less than 1km/h with 26" wheel
unsigned long minSpeedTime  = 225000; // Less than 33km/h with 26" wheel

unsigned long speedTime     = 0; // current speed timestamp in microseconds
unsigned long lastspeedTime = 0; // last speed timestamp in microseconds
unsigned long diffspeedTime = 0; // Difference between timestamps

uint8_t pin_MOSFET     = 4; // Digital pin of your transistor
uint8_t pin_Hallsensor = 5; // Digital pin of your hall switch for speed measurements

// updates wheel parameters (in m/s)
void updateWheel(double wz) {
  wheelsz = wz;
  wheel = wheelsz * 60 * 60 * 1000;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Cruise Control Tutorial");
  delay(1000);
  // initially set wheel size
  // we only need to calculate this once
  updateWheel(wheelsz); 

  // Pin settings
  pinMode(pin_MOSFET, OUTPUT);
  pinMode(pin_Hallsensor, INPUT);
  digitalWrite(pin_MOSFET, HIGH);
}

void loop() {
  // get the current timestamp
  speedTime=micros();
  // Now we calculate the difference between the timestamps 
  // (Here overflow is not catched for simplicity)
  diffspeedTime = speedTime - lastspeedTime;
  // we now check the current state of the hall switch
  // We assume a HIGH signal when the magnet passes the sensor
  // In addition, we check if the speet time is within the bounds of allowed speeds
  if (digitalRead(pin_Hallsensor) && diffspeedTime>minSpeedTime){
    // Now we calculate the speed
    speed = (double)wheel / diffspeedTime;
    Serial.print("Current Speed: ");
    Serial.print(speed);
    Serial.println(" km/h");
    // Save timestamp
    lastspeedTime = speedTime;
    // Now we control the motor
    if (speed>maxSpeed_kmh){ // Over the speed limit
      digitalWrite(pin_MOSFET, LOW); // Switch engine off
    }
    else{ // Under the speed limit
      digitalWrite(pin_MOSFET, HIGH); // Switch engine on
    }
  }
  else if (diffspeedTime>minSpeedTime){
    // Turn MOSFET on in case you stopped cycling
    digitalWrite(pin_MOSFET, HIGH); // Switch engine on
  }
}
