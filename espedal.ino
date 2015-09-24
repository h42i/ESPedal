#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Espanol.h>

#define DEBOUNCE 500

char *ssid     = "";
char *password = "";
char *broker   = "atlas.hasi";
int port       = 1883;

int pins[]={2,4,5};
int last[]={LOW,LOW,LOW};
int bounce_counter[]={0,0,0};

Espanol denada(ssid, password, broker, port, NULL);

void setup()
{
    for(int i=0;i<3;i++){
        pinMode(pins[i], INPUT_PULLUP);
    }   
}

void loop()
{
    denada.loop();
    
    char tmp[15];
    for(int i=0;i<3;i++){
        int current=digitalRead(pins[i]);
        if(current!=last[i]){
            bounce_counter[i]=DEBOUNCE;
        }
        else if(bounce_counter>0){
            bounce_counter[i]--;
        }
        if(bounce_counter[i]==1){
            sprintf(tmp,"hasi/espedal/%d",i+1);
            if(current==HIGH){
                denada.publish(tmp, "up");
            }
            else{
                denada.publish(tmp, "down");
            }
        }
        last[i]=current;
    }
}
