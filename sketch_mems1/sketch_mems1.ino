
/***************************
 * Example Sketch for the MEMS-1 Microphone
 * Board:Arduino Nano
 * Processdor: ATmega328P (old bootloader)
 * Started on November 15, 2019
 * Maicon Galiazzi
 */

// Connect the MEMS output to the Arduino A0 pin
int mic = A0;

// Variables to find the peak-to-peak amplitude of output
const int sampleTime = 50; 
int micOut;

void setup() {
  Serial.begin(115200);
}

void loop() {
   int micOutput = findPTPAmp();
  
   Serial.println(micOutput);

//Uncomment this line for help debugging (get the answer from A0 without treatment)
//   Serial.println(analogRead(mic)); 

   
}   


// Find the Peak-to-Peak Amplitude Function
int findPTPAmp(){
// Time variables to find the peak-to-peak amplitude
   unsigned long startTime= millis();  // Start of sample window
   unsigned int PTPAmp = 0; 
   unsigned int times = 0; 

// Signal variables to find the peak-to-peak amplitude
   unsigned int maxAmp = 0;
   unsigned int minAmp = 1023;

// Find the max and min of the mic output within the sampleTime timeframe
   while(millis() - startTime < sampleTime) 
   {
      micOut = analogRead(mic);
      if( micOut < 1023) //prevent erroneous readings
      {
        if (micOut > maxAmp)
        {
          maxAmp = micOut; //save only the max reading
        }
        else if (micOut < minAmp)
        {
          minAmp = micOut; //save only the min reading
        }
      }
      
   }

  PTPAmp = maxAmp - minAmp; // (max amp) - (min amp) = peak-to-peak amplitude
  
  double micOut_Volts = (PTPAmp * 3.3) / 1024; // Convert ADC into voltage
    
  //Uncomment the lines below for help debugging
//  Serial.println(micOut_Volts);
//  Serial.println(PTPAmp);
  

  //Return the PTP amplitude
  // You can also return the micOut_Volts to read the voltage level.
  return PTPAmp;   
}
