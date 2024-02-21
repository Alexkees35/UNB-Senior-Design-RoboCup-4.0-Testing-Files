#include "mbed.h"

// Define PWM pin
PwmOut pwmPinOne(PTD0);  // You can use a different PWM-capable pin if needed
PwmOut pwmPinTwo(PTC4);


int main() {
    wait_us(5000000);
    // Set PWM frequency and duty cycle for a constant 3.3V
    float targetVoltage = 3.3;  // Set your desired output voltage
    float vRef = 3.3;           // Reference voltage of the microcontroller

    float dutyCycle = targetVoltage / vRef;

    // Configure PWM
    pwmPinOne.period(0.001);  // 1 kHz frequency (adjust as needed)
    pwmPinOne.write(dutyCycle);
    pwmPinTwo.period(0.001);  // 1 kHz frequency (adjust as needed)
    pwmPinTwo.write(dutyCycle);

    // Main application loop
    while (1) {
        // Your main application code here
        // This loop is here to ensure your program keeps running
    }
}
