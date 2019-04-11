#include "pwm_dimmer.hpp"
#include "mbed.h"

DigitalOut led[]={(PD_15),(PD_13)};
PwmOut green[]={(PA_9)}
Timeout cout,blink;
InterruptIn botton(PA_0);

bool way=0;//0=DOWN; 1=UP

int main() {
    botton.rise(&set_timer); // start UP
    change_way();
}

void set_timer(){
    cout.attach(&change_intensity,1);
    botton.fall(&change_way);
}

void change_way(){
    cout.detach();
    Leds[way] = 0; // Change state of Led
    way = !way;  
    Leds[way] = 1; //1=more light (blue) ; 0=less light (orange)
}

void change_intensity(){

    botton.fall(&stop_blink);   // botton not press

    if(way==1){                //Increase 5% off max value per second
        if(green[0]<1.0){
            green[0] = green[0]+0.05;
            rise_blue();
        }

        if(green[0]>=1.0){       //Max value exceeded
            blink_blue();
        }

    }

    if(way==0){               //Decrease 5% of value same as before
        if(green[0]>0.0){
            green[0] = green[0]-0.05;
            fall_orange();
        }

        if(green[0]<=0.0){     //Min value exceeded
            blink_orange();
        }
    }
    cout.attach(&change_intensity, 1);
}

void rise_blue(){

    if(Leds[1]==1){
        Leds[1]=0;
        blink.attach(&rise_blue, 0.2);// blink blue in 0.2
    }
    else{
        Leds[1]=1;
    }

}


void fall_orange(){

    if(Leds[0]==1){
        Leds[0]=0;      // Orange off
        blink.attach(&fall_orange, 0.2); // blink orange for 0.2
    }

    else{
        Leds[0]=1;
    }

}


void stop_blink(){    //stop blink

    blink.detach();
    cout.detach();
    Leds[way]=1;

}


void blink_blue(){  

    Leds[1] = !Leds[1];
    cout.attach(&blink_blue, 0.2); // blink blue 5Hz 
    botton.fall(&change_way);

}


void blink_orange(){  

    Leds[0] = !Leds[0];
    cout.attach(&blink_orange, 0.2); // blink orange 5Hz
    botton.fall(&change_way);

}
