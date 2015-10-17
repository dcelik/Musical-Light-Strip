//#include <Adafruit_MotorShield.h>
//#include <Wire.h>
#include<fix_fft.h>

int pin_adc = A0;
char im[128];
char data[128]; 
int red = 9;
int green = 10;
int blue = 11;
 
void setup(){
  Serial.begin(9600);

  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  
}

void loop(){
 int static i = 0;
 static long tt;
 int val;
  
  if (millis() > tt){
     //if (i < 128){
     //if (i < 64){
     if (i < 32){
       val = analogRead(pin_adc);
       data[i] = (val*5)/4;
       //analogWrite(red,(val*3)/4);
       //analogWrite(blue,(val*3)/4);
       //analogWrite(green,(val*3)/4);
       //int temp = (val*3)/4;
       //Serial.println(data[i]+0);
       im[i] = 0;
       i++;
     }
     else{
       //Serial.println("Done Sampling");
       //this could be done with the fix_fftr function without the im array.
       fix_fft(data,im,5,0);
       // I am only interessted in the absolute value of the transformation
       for (i=0; i< 16;i++){
       //   int temp = sqrt(data[i] * data[i] + im[i] * im[i]);
          data[i] = sqrt(data[i] * data[i] + im[i] * im[i]); 
       //   if(i==0){
       //     rval = temp+0;
       //   }
       //   if(i>0 && i<17){
       //     gval += temp;
       //   }
       //   if(i>=17){
       //     bval += temp;
       //   }
       }
       int rval = (data[0]+data[1])/2;//*14;
       int bval = (data[3]+data[4]+data[5])/3;//*10;
       int gval = (data[6]+data[7])/2;//*12;
       float rsum = rval*pow((gval+bval-1),-1);
       float bsum = bval*pow((gval+rval-1),-1);
       float gsum = gval*pow((rval+bval-1),-1);
       //float rv = (rval+1)/(gval+bval+1);
       //float bv = (bval+1)/(gval+rval+1);
       //float gv = (gval+1)/(rval+bval+1);
       //rval = rv;
       //bval = bv;
       //gval = gv;
       //Serial.print(int(rsum)*80);
       //Serial.print(" ");
       //Serial.print(int(bsum)*80);
       //Serial.print(" ");
       //Serial.print(int(gsum)*80);
       //Serial.println(" ");
       if(!(int(rsum)==int(bsum) && int(bsum)==int(gsum))){
       analogWrite(red,(int(rsum))*80);
       analogWrite(blue,(int(bsum))*80);
       analogWrite(green,(int(gsum))*80);
       }
       //Serial.print(rv);
       //Serial.print(" ");
       //Serial.print(bv);
       //Serial.print(" ");
       //Serial.print(gv);
       //Serial.println(" ");
       //Serial.println("Done Populating FFT Data");
     }
   
   tt = millis();
  }
}

int getIndexOfMaximumValue(int* array, int size){
 int maxIndex = 0;
 int max = array[maxIndex];
 for (int i=1; i<size; i++){
   if (max<array[i]){
     max = array[i];
     maxIndex = i;
   }
 }
}
