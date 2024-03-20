#include "mbed.h"

BufferedSerial uart(PTC17, PTC16);

PwmOut Wheel1(PTD0);
AnalogOut Wheel2(DAC0_OUT);
PwmOut Wheel3(PTC4);

//AnalogOut Wheel2(PTB20);
//PwmOut Wheel2(PTD3);
PwmOut Servo(PTC3);
PwmOut Dribbler(PTC2);
PwmOut Wheel1Direction(PTA2);
PwmOut Wheel2Direction(PTD1);
PwmOut Wheel3Direction(PTA1);

PwmOut Wheel1Enable(PTC10);     //Might be an error
PwmOut Wheel2Enable(PTD2);
PwmOut Wheel3Enable(PTC2);   //Change




float pulse_width = 0.0015; // Pulse width for middle position (adjust as needed)
float pulse_width_left = 0.001; // Pulse width for left position (adjust as needed)
float pulse_width_right = 0.002; // Pulse width for right position (adjust as needed)
float servo_position = 0.5;

float servo_range = 180.0; // Servo motor range in degrees
float desiredVoltage;




void setServoPosition(float degrees) {
    // Map the degrees to the pulse width (adjust these values based on your servo)
    float pulse_width = 0.5 + degrees / 180.0; // Adjust these values as needed

    // Set the pulse width to move the servo to the desired position
    Servo.pulsewidth_ms(pulse_width);
}


    void servopulse(int angle){
        int pulsewidth=(angle*11)+500;  //The angle is converted to a pulse width value of 500-2480
        Servo.write(1);    //The servo interface level to the highest
        wait_us(pulsewidth);  //The number of microseconds of the delay pulse width value
        Servo.write(0);     //The servo interface level to low
        wait_us(20000-pulsewidth); //20000 can be replaced: "frequency = 1 / (20000/1000000)"
    }





int main(){
       	wait_us(5000000);
       	Wheel1Enable.write(1.0);
       	Wheel2Enable.write(1.0);
        Wheel3Enable.write(0);
        wait_us(1000000);
        Wheel1.write(1.0);
        Wheel2 = 1;
        //Wheel2.write(1.0);
        Wheel3.write(0/3.3);
        Wheel1Direction.write(1.0);
        Wheel2Direction.write(0.0);
}