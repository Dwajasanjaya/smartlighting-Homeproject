#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 
#define FIREBASE_HOST "https://realtime-c8232-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "FPWp3Xv1zlDgfpSKzaS3PaO8LhCLhyXS1zONEBuT"

#define WIFI_SSID "politeknik"
#define WIFI_PASS "polytechnic"

FirebaseData firebaseData;

#define ldrPin A0
#define relayPin D8

const float GAMMA = 0.7;
const float RL10 = 50;
//int counter = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ldrPin, INPUT);
  pinMode(relayPin, OUTPUT);
  lcd.init(); 
  lcd.backlight(); 
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting....");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected with IP : ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {

// These constants should match the photoresistor's "gamma" and "rl10" attributes
// Convert the analog value into lux value:
int analogValue = analogRead(ldrPin);
float voltage = analogValue / 1024. * 5;
float resistance = 2000 * voltage / (1 - voltage / 5);
float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
Serial.print("NilaiLDR = ");
Serial.println(lux);
lcd.setCursor(0, 0);
lcd.print("Nilai LDR: ");
lcd.print(lux);
Firebase.setFloat(firebaseData, "/nilaiLDR", lux);

//counter++;
  if(lux < 10){
  digitalWrite(relayPin, HIGH);
  lcd.setCursor(1,5);
  lcd.print("LED = ON");
  Firebase.setBool(firebaseData, "/relayState", true);
} else {
  digitalWrite(relayPin, LOW);
  lcd.setCursor(1,5);
  lcd.print("LED = OFF");
  Firebase.setBool(firebaseData, "/relayState", false);
}
}
