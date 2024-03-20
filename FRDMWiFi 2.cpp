#include "mbed.h"


//NOTE: 





BufferedSerial uart(PTC17, PTC16);

PwmOut Wheel1(PTD0);
AnalogOut Wheel2(DAC0_OUT);
PwmOut Wheel3(PTC4);

//AnalogOut Wheel2(PTB20);
//PwmOut Wheel2(PTD3);
PwmOut Servo(PTC3);
//PwmOut Dribbler(PTC2);
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






int main() {
    Servo.period(0.020);
    uart.set_baud(9600);
    desiredVoltage = 3.3;
    Wheel1.period(0.001);
    
    //Wheel2.period(0.001);
    Wheel3.period(0.001);
    Wheel1Direction.period(0.001);
    Wheel2Direction.period(0.001);
    Wheel3Direction.period(0.001);
//    Dribbler.period(0.001);
    Servo.period(0.001);
    Wheel1Enable.period(0.001);
    Wheel2Enable.period(0.001);
    Wheel3Enable.period(0.001);
    //Kicker = 1;



    float pulse_width_test = 0.002;
    float angle;



    char receivedData[5]; // Array to store the received command (4 characters + '\0')

    while (1) {

        
        if (uart.readable()) {
            // Read the first character
            char c;
            uart.read(&c, 1);

            // Check if the received character is the start of the command
            if (c == 'n' && uart.readable()) {
                //printf("Received 'n'\n");
                uart.read(&c, 1);

                // Print received character for debugging
                //printf("Received: %c\n", c);

                // Check if the second character is '/'
                if (c == '/') {
                    //printf("Received '/'\n");

                    // Read the next 4 characters
                    for (int i = 0; i < 4; i++) {
                        if (uart.readable()) {
                            uart.read(&c, 1);
                            receivedData[i] = c;
                            // Print received character for debugging
                            //printf("Received: %c\n", c);
                        } else {
                            // Handle the case where not enough characters are received
                            //printf("Incomplete command\n");
                            break;
                        }
                    }
                    receivedData[4] = '\0'; // Null-terminate the string

                    // Print received command for debugging
                    //printf("Received Command: %s\n", receivedData);

                    // Perform different actions based on the received command
                    if (strcmp(receivedData, "frwd") == 0) {
                        printf("Received Forward Command\n");
                        // Add your forward action here
                        
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




                    } else if (strcmp(receivedData, "bkwd") == 0) {
                        printf("Received Backward Command\n");
                        Wheel1Enable.write(1.0);
                        Wheel2Enable.write(1.0);
                        Wheel3Enable.write(0);
                        wait_us(1000000);
                        Wheel1.write(1.0);
                        Wheel2 = 1;
                        //Wheel2.write(1.0);
                        Wheel3.write(0/3.3);
                        Wheel1Direction.write(0.0);
                        Wheel2Direction.write(1.0);
                        // Add your backward action here
                    } else if (strcmp(receivedData, "left") == 0) {
                        printf("Received Left Command\n");
                        Wheel1Enable.write(1.0);
                        Wheel2Enable.write(1.0);
                        Wheel3Enable.write(1.0);
                        wait_us(1000000);
                        Wheel3Direction.write(1);
                        Wheel1.write(3.3/3.3);
                        Wheel2 = 1;
                        //Wheel2.write(0/3.3);
                        Wheel1Direction.write(1.0);
                        //Wheel2.write(0/3.3);
                        Wheel3.write(0.7654);
                        Wheel2Direction = 1.0;
                        Wheel3Direction.write(1.0);
                    } else if (strcmp(receivedData, "rigt") == 0) {
                        printf("Received Right Command\n");
                        Wheel1Enable.write(1.0);
                        Wheel2Enable.write(1.0);
                        Wheel3Enable.write(1.0);
                        wait_us(1000000);
                        Wheel3Direction.write(0);
                        Wheel1.write(3.3/3.3);
                        Wheel2 = 1;
                        Wheel1Direction.write(1.0);
                        //Wheel2.write(0/3.3);
                        Wheel3.write(0.7654);
                        Wheel2Direction = 1.0;
                        Wheel3Direction.write(0);
                        // Add your right action here
                    } else if (strcmp(receivedData, "stop") == 0) {
                        printf("Received Stop Command\n");
                        Wheel1Enable.write(0);
                        Wheel2Enable.write(0);
                        Wheel3Enable.write(0);
                        Wheel1.write(0/3.3);
                        Wheel2 = 0;
                        //Wheel2.write(0/3.3);
                        Wheel3.write(0/3.3);
//                        Dribbler.write(0);
                        //Kicker = 0;
                        // Add your stop action here
                    } else if (strcmp(receivedData, "kick") == 0) {
                        printf("Received Kick Command\n");
                        //Kicker = 1;
                        wait_us(1000000);
                        //Kicker = 0;
                        // Add your kick action here
                    } else if (strcmp(receivedData, "drbl") == 0) {
                        printf("Received Dribble Command\n");
//                        Dribbler.write(1);
                        wait_us(5000000);
//                        Dribbler.write(0);
                    } else if (strcmp(receivedData, "serv") == 0) {
                        printf("Received Servo Command\n");
                        Servo.period_ms(20);
                        Servo.pulsewidth_us(1000);  // 1000us pulse width for left position
                        wait_us(2000000);  // Wait for 2 seconds

                        // Point the servo to the center position
                        Servo.pulsewidth_us(1500);  // 1500us pulse width for center position
                        wait_us(2000000);  // Wait for 2 seconds

                        // Point the servo to the right position
                        Servo.pulsewidth_us(2000);  // 2000us pulse width for right position
                        wait_us(2000000);  // Wait for 2 seconds
                        
                        Servo.pulsewidth_us(1500);  // 1500us pulse width for center position
                        wait_us(2000000);  // Wait for 2 seconds

                    } else {
                        printf("Unknown Command\n");
                        // Add your handling for unknown commands
                    }
                }
            }
        }

        wait_us(100000); // Add a short delay to allow time for output in the serial monitor
    }
}




