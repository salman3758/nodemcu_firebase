#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
                          
#define FIREBASE_HOST "meter-gsm-default-rtdb.firebaseio.com"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "mFye9VZL4fQzootlQg1ySxwRLQSqQ3ddQsPcqoNc" //Your Firebase Database Secret goes here

#define WIFI_SSID "PTCL-BB"                                               //WiFi SSID to which you want NodeMCU to connect
#define WIFI_PASSWORD "pagal1234"                                      //Password of your wifi network 


int val=0, val3=1000;

void setup() {

  Serial.begin(115200);

  Serial.println("Serial communication started\n\n");  
           
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);


  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // connect to firebase
delay(1000);
}

void loop() { 

// Firebase Error Handling ************************************************
  if (Firebase.failed())
  { delay(500);
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Serial.println(Firebase.error());
  Serial.println("Connection to firebase failed. Reconnecting...");
  delay(500);
  }
  
 else { 
    Serial.println("Everything is ready!");
    delay(300); Serial.println("Everything is ready!");
    delay(300); Serial.println("Everything is ready! \n \n \n");
    delay(300);


    Firebase.setInt("/data",val);
   Serial.println(val);
    delay(300); Serial.println("uploaded val to firebase \n \n \n");

      Firebase.setInt("/test/val3",val3);
   Serial.println(val3);
    delay(300); Serial.println("uploaded val3 to firebase \n \n \n");
  

  val++; val3++;
 }



  
}
