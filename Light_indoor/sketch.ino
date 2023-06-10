#define BLYNK_TEMPLATE_ID "TMPL6sxUfX9Yq"
#define BLYNK_TEMPLATE_NAME "LED Control"
#define BLYNK_AUTH_TOKEN "6a44qzOCeQ2RY-l5wnBzmQsOoH2nQ_ie"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHTesp.h> //Library untuk DHT

char auth[] = BLYNK_AUTH_TOKEN ; //Auth Token

char ssid[] = "Wokwi-GUEST"; //nama hotspot yang digunakan
char pass[] = ""; //password hotspot yang digunakan

const int DHT_PIN = 15;

int value0, value1, value2, value3, value4, value5, value6;

byte LED_K1 = 26;
byte LED_K2 = 27;
byte LED_K3 = 14;
byte LED_K4 = 12;
byte LED_P1 = 13;
byte LED_P2 = 25;


DHTesp dht;

BlynkTimer timer;

//function untuk pengiriman sensor
void sendSensor()
{
 TempAndHumidity  data = dht.getTempAndHumidity();

//menampilkan temperature pada Serial monitor
Serial.print("% Temperature: ");
Serial.print(data.temperature);
Serial.println("C ");
Serial.print("% Kelembaban: ");
Serial.print(data.humidity);
Serial.println("% ");

Blynk.virtualWrite(V4, data.temperature); //mengirimkan data temperatur ke Virtual pin VO di Blynk Cloud
Blynk.virtualWrite(V5, data.humidity); //mengirimkan data kelemaban ke Virtual pin V1 di Blynk Cloud
}

BLYNK_WRITE(V0)
{
  value0 = param.asInt();
  digitalWrite(LED_K1, value0);
  Blynk.virtualWrite(V12, value0);
  cekAllLed();
}

BLYNK_WRITE(V1)
{
  value1 = param.asInt();
  digitalWrite(LED_K2, value1);
  Blynk.virtualWrite(V8, value1);
  cekAllLed();
}

BLYNK_WRITE(V2)
{
  value2 = param.asInt();
  digitalWrite(LED_K3, value2);
  Blynk.virtualWrite(V9, value2);
  cekAllLed();
}

BLYNK_WRITE(V3)
{
  value3 = param.asInt();
  digitalWrite(LED_K4, value3);
  Blynk.virtualWrite(V10, value3);
  cekAllLed();
}

BLYNK_WRITE(V7)
{
  value4 = param.asInt();
  digitalWrite(LED_P1, value4);
  Blynk.virtualWrite(V11, value4);
  cekAllLed();
}

BLYNK_WRITE(V8)
{
  value5 = param.asInt();
  digitalWrite(LED_P2, value5);
  Blynk.virtualWrite(V20, value5);
  cekAllLed();
}

BLYNK_WRITE(V6)
{
  value6 = param.asInt();

  digitalWrite(LED_K1, value6);
  Blynk.virtualWrite(V12, value6);
  Blynk.virtualWrite(V0, value6);
  
  digitalWrite(LED_K2, value6);
  Blynk.virtualWrite(V8, value6);
  Blynk.virtualWrite(V1, value6);

  digitalWrite(LED_K3, value6);
  Blynk.virtualWrite(V9, value6);
  Blynk.virtualWrite(V2, value6);

  digitalWrite(LED_K4, value6);
  Blynk.virtualWrite(V10, value6);
  Blynk.virtualWrite(V3, value6);
  
  digitalWrite(LED_P1, value6);
  Blynk.virtualWrite(V11, value6);
  Blynk.virtualWrite(V7, value6);

  digitalWrite(LED_P2, value6);
  Blynk.virtualWrite(V20, value6);
  Blynk.virtualWrite(V8, value6);
}

void cekAllLed(){
  if(value0 == 1 && value1 == 1 && value2 == 1 && value3 == 1 && value4 == 1 && value5 == 1){
    Blynk.virtualWrite(V6, 1);
  }
  else{
    Blynk.virtualWrite(V6, 0);
  }
  // if(value0 == 0 && value1 == 0 && value2 == 0 && value3 == 0){
  //   Blynk.virtualWrite(V6, 0);
  // }
}

void setup()
{
// Debug console
Serial.begin(115200); //serial monitor menggunakan bautrate 9600
dht.setup(DHT_PIN, DHTesp::DHT22);
pinMode(LED_K1, OUTPUT);
pinMode(LED_K2, OUTPUT);
pinMode(LED_K3, OUTPUT);
pinMode(LED_K4, OUTPUT);
pinMode(LED_P1, OUTPUT);
pinMode(LED_P2, OUTPUT);
Blynk.begin(auth, ssid, pass); //memulai Blynk
timer.setInterval(1000, sendSensor); //Mengaktifkan timer untuk pengiriman data 1000ms
}

void loop()
{

Blynk.run(); //menjalankan blynk
timer.run(); //menjalankan timer
}


