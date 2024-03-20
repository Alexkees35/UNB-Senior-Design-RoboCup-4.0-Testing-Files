#include "mbed.h"

BufferedSerial uart(PTC17, PTC16);

AnalogOut Wheel1(DAC0_OUT);
PwmOut Wheel2(PTC11);
PwmOut Wheel3(PTC4);
PwmOut Wheel1Direction(PTA2);
PwmOut Wheel2Direction(PTD1);
PwmOut Wheel3Direction(PTA1);
PwmOut Wheel1Enable(PTC10);     
PwmOut Wheel2Enable(PTD2);
PwmOut Wheel3Enable(PTC2);   //Change






int main(){
    float speed = 0;
    float increment = 0.01;
    int times;
    Wheel1Direction.write(1.0);
    Wheel2Direction.write(0.0);
    Wheel1Enable.write(1.0);
    Wheel2Enable.write(1.0);
    Wheel3Enable.write(0);
    for (times = 1; times<=20; times++){
        wait_us(100000);
    }
                       
                            //Remember Wheel 1 was 33% and wheel2 was 30% 
    Wheel3.write(0/3.3);
    Wheel1.write(0.10+0.022);
    Wheel2.write(0.10);
    wait_us(2500000);
    Wheel1Enable.write(0);
    Wheel2Enable.write(0);

    wait_us(1000000);

    Wheel1Direction.write(0.0);
    Wheel2Direction.write(1.0);
    Wheel1Enable.write(1.0);
    Wheel2Enable.write(1.0);
    Wheel3Enable.write(0);
    Wheel3.write(0/3.3);
    Wheel1.write(0.10+0.022);
    Wheel2.write(0.10);
    wait_us(2500000);
    Wheel1Enable.write(0);
    Wheel2Enable.write(0);


}