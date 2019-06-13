/*     Simple Stepper Motor Control Exaple Code
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
// defines pins numbers
const int stepPin = 4; 
const int dirPin = 3;
const int enablePin = 2;
const int buttonPin = 5;
int analog1;
int analog2;
const int stepsRev = 400;  // Number of steps to make a full revolution of your stepper
const int dialNumb = 100;  // How many numbers are on the dial
const int stepFreq = 400;  // frequency to drive stepper in Hz
const int delayMS = 1000 / stepFreq / 2 ; // number of milliseconds to hold step pulse (1/2 the period)
const bool CW = 0;
const bool CCW = 1;
const int visualDelay = 10; // number of miliseconds to pause at each number
int location = -1;  // Dial Location, Will be set to 0 as part of setup sequence.
 
void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enablePin,OUTPUT);
  pinMode(buttonPin,INPUT_PULLUP);
}

/*
 * void step(int x, bool dir)
 * Moves in specified direction for x numbers on the dial 
 * Using dir : 1 for CCW, 0 for CW
*/
void myStep(int x, bool dir) {
  digitalWrite(dirPin,dir);  // 1 for CCW, 0 for CW
  int step = stepsRev / dialNumb * x ;  // Compute the nubmer of steps
  for(int i =0; i < step; i++) {
    digitalWrite(stepPin,LOW); 
    delay(delayMS); 
    digitalWrite(stepPin,HIGH); 
    delay(delayMS);
  }  
}

/*
 * int toNumber(int b, int a bool dir)
 * Moves in specified direction from a to b on the dial 
 * Useing dir : 1 for CCW, 0 for CW
*/
int toNumber(int b, int a, bool dir) {
  int x =  a - b ;  // How far apart are the numbers?
  if (x > 0){  // If the short trip is CW
    if (dir){  // and direction is CCW
      x = dialNumb - x;  // Go the long way round
    }
  }
  if (x < 0){  // If the short trip is CCW 
    if (dir){  // and the direction is CCW
      x = abs(x);  // Go, but with a postive int
    }
    else{  // If the direction is CW
      x = dialNumb + x;  // Go the long way round
    } 
  }
  if (a == b ) {  // If target and location are the same 
    x = 100;  // Make an entire trip
  }
  myStep(x, dir);  // Drive the stepper motor
  return b;
}

void loop() {
  if (!digitalRead(buttonPin) && ( location != -1 ) )
  { // Don't enter untill the switch is flipped (and dial is at 0)
    digitalWrite(stepPin,HIGH);  // Start at the HIGH level
    digitalWrite(enablePin,HIGH); // Enable Stepper Driver

    location = toNumber(location,location,CCW);  // Turn Cam, Pickup Wheel 3
    location = toNumber(location,location,CCW);  // Turn Wheel 3, Pickup Wheel 2
    location = toNumber(location,location,CCW);  // Turn Wheel 2, Pickup Wheel 1
    for(int firstNumber = 0; firstNumber < 100; firstNumber++) {
      location = toNumber(firstNumber,location,CCW); // Enter First Number
      delay(visualDelay);
      location = toNumber(location,location,CW);  // Turn Cam, Pickup Wheel 3
      location = toNumber(location,location,CW);  // Turn Wheel 3, Pickup Wheel 2
      for(int secondNumber = 99; secondNumber >= 0; secondNumber-- ) {
        location = toNumber(secondNumber,location,CW); // Enter Second Number
        delay(visualDelay);
        location = toNumber(location,location,CCW);  // Turn Cam, Pickup Wheel 3
        for (int thirdNumber = 0; thirdNumber < 100; thirdNumber++) {
          location = toNumber(thirdNumber,location,CCW); // Enter Third Number
          delay(visualDelay);
          //Rember to check for cam engagement
          Serial.print("Checking: ");
          Serial.print(firstNumber);
          Serial.print(" - ");
          Serial.print(secondNumber);
          Serial.print(" - ");
          Serial.print(thirdNumber);
          Serial.println();
          location = toNumber(0,location,CW); // Turn Clockwise to 0
          location = toNumber(80,location,CW); // Turn Clockwise to 80 to check
          delay(visualDelay);
          location = toNumber(0,location,CCW); // Ensure we move the right way as we check next
          //location = toNumber(thirdNumber,location,CCW); // Move back to third number 
        } // thirdnumber loop
        
      } // secondnumber loop
      
    } // firstnumber loop

  } // if searching loop
  else {
  location = 0;  
  }
}
