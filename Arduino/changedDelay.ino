#include <Adafruit_NeoPixel.h>
#include <MsTimer2.h>


#define PIN 6
#define LEDNUM 35


double bpm = 100.0;
double interval = 60.0/bpm;
double cal_time = 0; // for calculating accuracy
double start_time = 0;

int pattern[16]={1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0};
int threshold=70;
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

}

// the loop routine runs over and over again forever:
void loop() {
  
 
  // read the input on analog pin 0:
  int sensorValue = analogRead(A5);
  // print out the value you read:
  if(sensorValue>threshold)
  {
   strip.clear();
   strip.show();
   a[0]=sensorValue;
   delay(10); 
   Serial.println(a[0]);
   delay(100);
   for(j = 0 ; j <= LEDNUM ; j++){
        strip.setPixelColor(j,0,255,255);
      }
   strip.show();
   delay(10);
   strip.clear();
   strip.show();
   
    
  }  // delay in between reads for stability
}

