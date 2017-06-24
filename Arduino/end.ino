#include <MsTimer2.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define LEDNUM 35

double bpm = 90.0;
double interval = 60.0/bpm;
double tt = interval*1000;
double half_tt = tt/2;
double pre_time = 0;
double cal_time = 0; // for calculating accuracy
double start_time = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDNUM, PIN, NEO_GRB + NEO_KHZ800);

int threshold=4;
int a[1];
int pattern[16]={1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0};
int i = 0;
int j = 0;

void setup() {
  Serial.begin(9600);
  strip.begin();
  MsTimer2::set(tt,check_tempo);
  strip.setBrightness(10);
  strip.clear();
  strip.show();  
  for(int k = 4; k > 0 ; k--){
    for(j = 0; j <= LEDNUM; j++){
      strip.setPixelColor(j,0,255,255);
    }
    strip.setBrightness(10);
    strip.show();
    delay(half_tt);    
    strip.clear();
    strip.show();
    delay(half_tt);    
  }
  MsTimer2::start();
}

void loop(){
}

void check_tempo(){
  double start_time = millis();
  strip.clear();
  strip.show();
  delay(half_tt);  
  
  int sensorValue = analogRead(A5);
  a[0] = sensorValue;
  
  i = i%16;
 
  if(sensorValue>threshold){
    double check_time = millis();
    double cal_time = check_time - start_time;
     if(tt-700<cal_time||cal_time< tt+700){
      if(pattern[i] == 1){    //Good
        Serial.println(a[0]);
        for(j = 0 ; j <= LEDNUM ; j++){
           strip.setPixelColor(j,0,0,255);
        
        }
      }
      else{
        Serial.println(a[0]);  //Wrong note
        for(j = 0 ; j <= LEDNUM ; j++){
           strip.setPixelColor(j,255,255,255);
        }
      }
    }
    else{
      Serial.println(a[0]);    //Miss
      for(j = 0 ; j <= LEDNUM ; j++){
         strip.setPixelColor(j,0,255,0);
      }
    }
  } 
  else{                      
    Serial.println(a[0]);     //Failed                 
    for(j = 0 ; j <= LEDNUM ; j++){
       strip.setPixelColor(j,255,0,0);
    }
  }
  strip.show();
  delay(half_tt);
  i++;
}


