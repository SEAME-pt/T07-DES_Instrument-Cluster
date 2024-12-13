//www.elegoo.com
//2023.05.06

#include "Stepper.h"
#include "IRremote.h"

/*----- Variables, Pins -----*/
#define STEPS  32   // Number of steps per revolution of Internal shaft
int  Steps2Take;  // 2048 = 1 Revolution
int receiver = 12; // Signal Pin of IR receiver to Arduino Digital Pin 12

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4

Stepper small_stepper(STEPS, 8, 10, 9, 11);
IRrecv irrecv(receiver);    // create instance of 'irrecv'
uint32_t last_decodedRawData = 0;//vairable uses to store the last decodedRawData

void setup()
{
  irrecv.enableIRIn(); // Start the receiver
}

void loop()
{
  if (irrecv.decode()) // have we received an IR signal?
  {
    // Check if it is a repeat IR code
    if (irrecv.decodedIRData.flags)
    {
      //set the current decodedRawData to the last decodedRawData
      irrecv.decodedIRData.decodedRawData = last_decodedRawData;
    }
    switch (irrecv.decodedIRData.decodedRawData)
    {

      case 0xB946FF00: // VOL+ button pressed
        small_stepper.setSpeed(500); //Max seems to be 500
        Steps2Take  =  -2048;  // Rotate CW
        small_stepper.step(Steps2Take);
        delay(2000);
        break;

      case 0xEA15FF00: // VOL- button pressed
        small_stepper.setSpeed(500);
        Steps2Take  =  2048;  // Rotate CCW
        small_stepper.step(Steps2Take);
        delay(2000);
        break;

    }
    //store the last decodedRawData
    last_decodedRawData = irrecv.decodedIRData.decodedRawData;
    irrecv.resume(); // receive the next value
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }

}/* --end main loop -- */