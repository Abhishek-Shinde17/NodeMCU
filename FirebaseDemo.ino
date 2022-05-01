
#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>

#define _SSID "vivo 1906"        // Your WiFi SSID
#define _PASSWORD "yuktaA2005"    // Your WiFi Password
#define PROJECT_ID "socitysecurityapplication-default-rtdb"   // Your Firebase Project ID. Can be found in project settings.


Firebase firebase(PROJECT_ID);    // SLOW BUT HASTLE-FREE METHOD FOR LONG TERM USAGE. DOES NOT REQUIRE PERIODIC UPDATE OF FINGERPRINT

void setup() {
  Serial.begin(115200);
  pinMode(A0 , INPUT);
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  firebase.setString("control_system/LIGHT16" ,(String)11 );
}
int flag16 = 0;
int flag5 = 0;

void loop() {
  String data = firebase.getString("control_system/LIGHT16");
  Serial.print(data);  
  if(data == "16"){
    if(flag16 == 0){
      digitalWrite(16 , HIGH);
      digitalWrite(5 , HIGH);
      flag16=1;
      firebase.setString("control_system/LIGHT16" ,(String) flag16);
    }
    else{
      if(flag16 == 1){
      digitalWrite(16 , LOW);
      flag16=0;
      digitalWrite(5 , LOW);
      firebase.setString("control_system/LIGHT16" ,(String) flag16);
     }
    }
  }
  if(data == "00"){
    int LDR = analogRead(A0);
  Serial.println(LDR);
  if(LDR >=800){
    digitalWrite(16 , LOW);
    digitalWrite(5 , LOW);
  }
  else{
    digitalWrite(16 , HIGH);
    digitalWrite(5, HIGH);
    }
  }  
  
}
