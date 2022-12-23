#define BLYNK_TEMPLATE_ID "TMPLzwOGZjnO"
#define BLYNK_DEVICE_NAME "Trần Duy Hiệu"
#define BLYNK_AUTH_TOKEN "m8Rq2VyPZkvOabcvg3tdZEBoMcdvzQD0"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "la la la";
char pass[] = "";

int Button = 4;
int led_status = LOW;
unsigned long last_interrupt  = 0;
ICACHE_RAM_ATTR void blink_relay1(){
  unsigned long now = millis();
  if (now - last_interrupt >200)
  {
    if (led_status== LOW)
    {
      led_status = HIGH;
    }
    else if (led_status== HIGH ){
      led_status = LOW;
    }
    digitalWrite(D1,led_status ); 
  }
  last_interrupt = now;
}
BlynkTimer timer;
BLYNK_WRITE(V0)
{
    int pinValueA = param.asInt(); 
    if (pinValueA == 1)
    {
      Serial.print(1);
      digitalWrite(D0, HIGH);
    }
    else
    {
      Serial.println(0);
      digitalWrite(D0, LOW);
    }
}


BLYNK_WRITE(V1)
{
    int pinValueB = param.asInt(); 
    if (pinValueB == 1)
    {
      if (led_status== LOW)
      {
        led_status = HIGH;
      }
      else if (led_status== HIGH ){
        led_status = LOW;
      }
      digitalWrite(D1,led_status );
    }
}

BLYNK_WRITE(V3)
{
    int pinValueB = param.asInt(); 
    if (pinValueB == 1)
    {
      Serial.println(3);
      digitalWrite(D3, HIGH);
    }
    else
    {
      Serial.println(0);
      digitalWrite(D3, LOW);
    }  
}
BLYNK_WRITE(V4)
{
    int pinValueB = param.asInt(); 
    if (pinValueB == 1)
    {
      Serial.println(4);
      digitalWrite(D4, HIGH);
    }
    else
    {
      Serial.println(0);
      digitalWrite(D4, LOW);
    }  
}
BLYNK_WRITE(V5)
{
    int pinValueB = param.asInt(); 
    if (pinValueB == 1)
    {
      Serial.println(5);
      digitalWrite(D5, HIGH);;
    }
    else
    {
      Serial.println(0);
      digitalWrite(D5, LOW);
    }  
}
BLYNK_WRITE(V6)
{
    int pinValueB = param.asInt(); 
    if (pinValueB == 1)
    {
      Serial.println(6);
      digitalWrite(D6, HIGH);
    }
    else
    {
      Serial.println(0);
      digitalWrite(D6, LOW);
    }  
}
BLYNK_CONNECTED()
{
    Blynk.syncVirtual(V0);
    Blynk.syncVirtual(V1);
    Blynk.syncVirtual(V2);
    Blynk.syncVirtual(V3);
    Blynk.syncVirtual(V4);
    Blynk.syncVirtual(V5);
    Blynk.syncVirtual(V6);
}

void myTimerEvent()
{
  Blynk.virtualWrite(V2,led_status );
}

void setup()
{
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, INPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    attachInterrupt(Button, blink_relay1, FALLING);
    timer.setInterval(100L, myTimerEvent);
}

void loop()
{
    Blynk.run();
    timer.run();
}