
#include <FlexiTimer2.h>

#include <Adafruit_NeoPixel.h>

#define PIN 6
#define LEDNUM 35


double bpm = 60.0;
double interval = 60.0/bpm;
double tt = interval*1000;
double cal_time = 0; // for calculating accuracy
double start_time = 0;

int pattern[3000]={1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0};
int threshold=65;
int a[1];
int i = 0;
int j = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDNUM, PIN, NEO_GRB + NEO_KHZ800);
// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(10);
  strip.clear();
  strip.show();
  FlexiTimer2::set(100,1.0/3000,print);
  double start_time = millis();
  FlexiTimer2::start();  

}


void print()
{
  // read the input on analog pin 0:
  int sensorValue = analogRead(A5);
  // print out the value you read:
  if(sensorValue>threshold)
  {
   double check_time = millis();
   double cal_time = check_time - tt*int(cal_time/interval/1000);
   
   Serial.println(tt*int(cal_time/interval/1000));
   Serial.println(check_time);
   Serial.println(tt*int(cal_time/interval/1000) + tt/2);
   
   strip.clear();
   strip.show();
   a[0]=sensorValue;
   delay(10); 
   Serial.println(a[0]);
   delay(100);
   Serial.println(int(cal_time/interval/1000));
   /*if(tt*int(cal_time/interval/1000)< check_time<tt*int(cal_time/interval/1000) + tt/2)
   {
      if(pattern[0] == 1)
      {    //Good
        Serial.println(a[0]);
        for(j = 0 ; j <= LEDNUM ; j++)
        {
           strip.setPixelColor(j,0,0,255);
        }
      }
   }
   else
   {
      
      for(j = 0 ; j <= LEDNUM ; j++)
      {
         strip.setPixelColor(j,0,255,0);
      }
   }*/
   strip.show();
   delay(10);
   strip.clear();
   strip.show();   
  } 
  
  // delay in between reads for stability
}

// the loop routine runs over and over again forever:
void loop() {
}

