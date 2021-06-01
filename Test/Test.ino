#include <SoftwareSerial.h>


SoftwareSerial espSerial(5, 6);
String str;
void setup(){
Serial.begin(115200);
delay(2000);
}
void loop()
{
float h = 300;
// Read temperature as Celsius (the default)
float t = 400;
Serial.print("H: ");
Serial.print(h);
Serial.print("% ");
Serial.print(" T: ");
Serial.print(t);
Serial.println("C");
str =String("coming from arduino: ")+String("H= ")+String(h)+String("T= ")+String(t);
espSerial.println(str);

String a= String("Modiied")+espSerial.readString();
Serial.println(a);
delay(1000);
}
