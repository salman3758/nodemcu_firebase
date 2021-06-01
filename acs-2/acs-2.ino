#define PIN A0
float resolution  = 3.3 / 1024;                   // Input Voltage Range is 1V to 3.3V
                                                  // ESP8266 ADC resolution is 10-bit. 2^10 = 1024

uint32_t period = 1000000 / 60;                   // One period of a periodic waveform
uint32_t t_start = 0;                                 

// setup
float zero_ADC_Value = 0, zero_voltageValue = 0;   

// loop
float ADC = 0, Vrms = 0, Current = 0, Q = 0.0147;
float sensitivity = 0.100;                        // 185 mV/A, 100 mV/A and 0.66 mV/A for ±5A, ±20A and ±30A current range respectively. 

void setup()
{
  Serial.begin(115200);                           // Initialize Serial communication
  pinMode(PIN, INPUT);                            // Set pin A0 as read.  
  /*--------NodeMCU--------*/
  t_start = micros();                             
  uint32_t ADC_SUM = 0, n = 0;
  while(micros() - t_start < period) {            
    ADC_SUM += analogRead(PIN);                   // reading the analog value from pin A0. 
    n++;                                          // counter to be used for avg. 
  }
  zero_ADC_Value = (ADC_SUM / n);                 // The avg analog value when no current pass throught the ACS712 sensor.
  zero_voltageValue = zero_ADC_Value * resolution;    // The ACS712 output voltage value when no current pass trough the sensor (i = 0)

}
void loop() {
  
  /*----Vrms & Irms Calculation----*/
  t_start = micros();                             
  uint32_t ADC_Dif = 0, ADC_SUM = 0, m = 0;        
  while(micros() - t_start < period) {            // Defining one period of the waveform. US frequency(f) is 60Hz. Period = 1/f = 0.016 seg = 16,666 microsec
    ADC_Dif = zero_ADC_Value - analogRead(PIN);   // To start from 0V we need to subtracting our initial value when no current passes through the current sensor, (i.e. 750 or 2.5V).
    ADC_SUM += ADC_Dif * ADC_Dif;                 // SUM of the square
    m++;                                          // counter to be used for avg.
  }
  ADC = sqrt(ADC_SUM / m);                        // The root-mean-square ADC value. 
  Vrms = ADC * resolution ;                       // The root-mean-square analog voltage value.   
  Current = (Vrms  / sensitivity) - Q;        // The root-mean-square analog current value. Note: Q
  //------------------------------//
  
  Serial.print("analogRead = ");
  Serial.println(analogRead(PIN));
  
  Serial.print("Vrms = ");                        
  Serial.print(Vrms, 6);
  Serial.println(" V");        

  Serial.print("Irms = ");                       
  Serial.print(Current, 6);
  Serial.println(" A");
  Serial.print("\n");
  
  delay(1000); 
}
