#include <Time.h>
#include <TimeLib.h>
#include <SPI.h> 
#include <Ethernet.h>
#include <Twitter.h>

int sensor = 7;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 111, 1, 111 };
Twitter twitter("TOKEN");
char msg[] = "Wassereinbruch,";
char msg2[128];
boolean msgSent= false;

void setup()
{
 Serial.begin(9600);
 pinMode(sensor, INPUT);
 digitalWrite( sensor, HIGH);
}

void loop()
{
  if (digitalRead(sensor) == LOW) {
     if (msgSent== false) {
    delay(1000);
  Ethernet.begin(mac, ip);
   sprintf(msg2, "%s  %d:%d:%d", msg, hour(), minute(), second()); 
  Serial.println("connecting ...");
  if (twitter.post(msg2)) {
     
    int status = twitter.wait(&Serial);
       msgSent= true;    
    if (status == 200)
       
      {
      Serial.println("OK.");
    } 
    else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  } 
  else {
    Serial.println("connection failed.");
  }
  }
}
else {
  msgSent= false;
  }
}


