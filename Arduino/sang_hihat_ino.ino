#include <Adafruit_NeoPixel.h>
#define PIN 6
#define LEDNUM 35
//sang hihat
int pattern[16]= {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDNUM, PIN, NEO_GRB + NEO_KHZ800);
// the setup routine runs once when you press reset:
double bpm=120;
double interval =500;
int threshold=70;
int a[1];
int i=0;
int j=0;

void setup() {
  Serial.begin(9600);
}
void loop(){
  int sensorValue = analogRead(A5);
  if(sensorValue>threshold)
  {
   a[0]=sensorValue;
   delay(10); 
   Serial.println(a[0]);
   delay(100);
   start();
}  
}
void start(){
for(i=0;i<16;i++){
  if(pattern[i]==1){for(j = 0 ; j <= LEDNUM ; j++)
  {
        strip.setPixelColor(j,0,255,255);
      }
   strip.show();
   delay(30);
   strip.clear();
   strip.show();
   delay(470);
  }
  else
  {delay(500);}

}
}
