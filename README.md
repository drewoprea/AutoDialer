# AutoDialer
Quick and Dirty AutoDialer

Uses an Arduino and a bipolar stepper to exhaustively traverse the combination space of a three wheel combination lock.

Set stepPin, dirPin, enablePin, and buttonPin for your circuit.
analog1 and analog2 are for stepper feedback (future use)
stepsRev = the number of stepper pulses needed for one revolution (depends on your stepper and driver)
dialNumb = the number of real positions on the dial (inexpensive locks mav have as few as 30)
stepFreq = how fast can we drive the stepper? Frequency is in Hz
delayMS is normally calculated from stepFreq
visualDelay = how long should the dialer pause on each number? Delay is in milliseconds

On startup nothing will move until you index the dial to 0, and short buttonPin to ground
 
