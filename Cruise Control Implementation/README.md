# Technical Instructions for eBike Cruise Control

Creating a cruise-controlled eBike or eScooter is straightforward with basic knowledge of electrical engineering and soldering. This tutorial provides a simple example of how to achieve this. 

*Note*: Be aware that you may loose your warranty if you modify your eBike. All given instructions are at your own risk and should only be done by professionals. We do not take responsibility for any changes you make, damages and/or violation of your local traffic rules and only share this tutorial for research purposes.

## How it works

Brushless 3-phase DC motors, commonly used in eBikes and eScooters, measure speed using three internal digital hall sensors. These sensors detect the presence of a magnetic field and switch their output when a field is detected. For a detailed explanation, watch this video by AndySV1K on  [Youtube](https://www.youtube.com/watch?v=jfIJvESYOtA) 

The bike's internal controller uses the hall sensor outputs to measure the current speed and then control the motor. When the sensors indicate no changes over time, the motor is turned off as the controller assumes the bike is stationary. We exploit this feature by making the system think the wheels are stationary at a desired speed, thus implementing Cruise Control technology for DC motors.

## Required Electrical Components

Only a few simple parts are required to add Cruise Control to an eBike. More advanced implementations require deeper knowledge of the bike and its controller. Our simple method makes the controller think the bike is stationary. While this could be achieved by switching the hall sensor outputs, we use a simpler approach.

We require a single logic-level N-channel transistor for switching, placed between the hall switches and the GND wire. This way, current flows only when there is a HIGH signal at our transistor. By cutting the black wire and inserting our switch, we can handle speed modifications up to the maximum supported speed. Alternatively, a logic-level P-channel transistor can be used between the red wire (+5V power source of the hall switches). A pull-up resistor will turn the transistor on in its initial state, allowing electrical power use without a microcontroller.

### Example Required Parts

- 1x FDP5800 or IRFZ44N logic-level N-MOSFET
- 1x 200-1k Resistor
- 1x 100k Resistor
- 1x Hall sensor, for example PIC H501
- 1x Neodym magnet (r=10mm, w=3mm)
- 1x Insulating tape
- 1x Glue Gun
- 1x some small wires for soldering
- 1x prototype PCB

### Schematics

The following schematic shows how your n-MOSFET should be build. I use simple prototyping boards. Feel free to make you own design. 

![](https://www.electronics-tutorials.ws/wp-content/uploads/2013/09/tran57.gif?fit=267%2C146?fit=267,226)

Rin should be between 200 to 1000Ohms. Resistor RL is the hall sensors. Between the pins (G) and (S) of your logic-level MOSFET we additionally add a 100k resistor. The signal Vin should be connected to your microcontroller. By applying a HIGH signal on Vin, your e-bike motor will turn on. If you want to learn more about how MOSFET and this schematic work please refer to  [electronics-tutorials](https://www.electronics-tutorials.ws/transistor/tran_7.html) 

## Mounting the Hardware

Depending on your bike, you may need to modify this tutorial. Some bikes use external reed switches with two wires, where the same technology with little modifications can be applied.

### Cable
Locate the cable from your DC motor to the controller. There are many different cables, we here refer to the commonly used 9 pin HiGo Main Signal cable. You can find a list and pinouts here: [Link](https://ebikes.ca/learn/connectors.html). If you have no access to the direct wires in your e-bike controller, carefully remove the outer insulation. If you use a N-channel transistor locate the black wire (GND) among the nine wires inside. For P-channel transistor, locate the small red wire (+5V). Depending on your cable, the black wire might be hidden underneath the outer wires. Cutting or detaching this wire should stop the engine from turning on. In the following picture you see an example of the modifications:


If your motor stops working, you should be able now to turn the motor on and off with a transistor and you can continue with the tutorial.

### Solder Wires

Solder a wire to each end of the cut wire for the transistor. The wire connected to the controller is the GND, while the other is the input signal. Using a logic-level N-MOSFET, connect the GND to the Source (S) of the MOSFET and the other end to the hall switches, connected to the Drain (D). The Gate (G) is connected via a 100k Ohm resistor to GND and a 200-1k Ohm resistor to your microcontroller. Here is an example of a successful modified cable:


### Isolate Cable

Isolate your hardware from water and mud after cutting the wires using insulating tape, liquid, and a glue gun. Isolate your solder joints with tape or liquid tape (allow it to dry). Then cover all cables with heated glue and use insulating tape again to cover the cut wire. Though not standardized, this method can effectively protect cables for years from my experience. The transistor can also be covered using this method. However, be aware that you probably need some soldering practice before you can modify cables that last long. 
Now here is the final modification:


## Speed Measurement

To measure speed, use the magnet and a hall switch. You'll also need the wheel circumference, which is typically printed on the tire. For instance, a 26" 44-559 tire corresponds to a circumference of 2.033m. A list can be found [here](https://pendix.com/service/instruction-manual/operation-pendixbike-pro/drive). Attach your hall sensor to the frame near the wheel and mount the magnet on the spoke that passes the sensor to measure your bike's speed. This method is similar to how inexpensive cycling computers measure speed. Use the hall switch output signal as an input for your Arduino to measure speed. 


## Speed calculation

To calculate the current speed, use the wheel circumference and the time between the last and current timestamp when the magnet passed the hall switch. The equation is:

```C++
double speed_kmh = (wheelcircumference_in_m * 60 * 60 * 1000)/ speedTime_in_us;
```

Using the circumference in meters and the time in microseconds since the last hall sensor trigger, you can calculate the speed in km/h. Multiply this value by 0.621371 to convert to miles per hour.


## Basic Code example for Arduino

To start implementing your own Cruise Control technology for eBikes, we provide a basic example sketch for Arduino. This code measures the speed of your eBike by using the hall sensor's signal and then switches your transistor on and off depended on your set speed limit.

```C++
/************************************************************************
*
*       Basic example of a Cruise Control technology for eBikes
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

uint8_t pin_MOSFET     = 5; // Digital pin of your transistor
uint8_t pin_Hallsensor = 4; // Digital pin of your hall switch for speed measurements

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


```

## License

[MIT](https://choosealicense.com/licenses/mit/)
 
