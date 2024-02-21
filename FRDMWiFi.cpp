#include "mbed.h"

//BufferedSerial pc(USBTX, USBRX, 9600);
Serial pc(USBTX, USBRX);
AnalogOut DAC(DAC0_OUT);

void processUARTCommand() {
    char command[3];  // Assuming commands are 2 characters long plus null terminator
    int bytesRead = 0;

    while (bytesRead < 2 && pc.readable()) {
        pc.read(&command[bytesRead], 1);
        bytesRead++;
    }

    if (bytesRead > 0) {
        command[bytesRead] = '\0';  // Null-terminate the string

        pc.printf("Received command: %s\r\n", command);

        if (strcmp(command, "ON") == 0) {
            // Turn on DAC0_OUT
            // Your DAC control code here
            DAC = 1.0;
            pc.printf("DAC turned ON\r\n");

        } else if (strcmp(command, "OFF") == 0) {
            // Turn off DAC0_OUT
            // Your DAC control code here
            DAC = 0.0;
            pc.printf("DAC turned OFF\r\n");

        } else {
            // Unknown command, handle accordingly
            pc.printf("Unknown command\r\n");
        }
    } else {
        pc.printf("No valid command received\r\n");
    }
}

int main() {
    pc.set_baud(9600);

    while (1) {
        if (pc.readable()) {
            processUARTCommand();
        }

        // Add any necessary code for the main loop here
    }
}
