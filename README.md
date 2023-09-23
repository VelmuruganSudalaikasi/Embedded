# Embedded
Embedded repostitory contains the Embedded Basic and communication protocols.

Platform Details:

MICRO-PROCESSOR : PIC

DESIGN          : PROTEUS

IDE             : MP LAB

Note: Each task have separate directory.


1. Blinking the LEDs connected to PORTC pins.

2. Program to blink the LEDs connected on RC1 and RC2. The LED blinking pattern for RC1 and RC2 is 10, 01, 00, 11, each with a one-second delay.

3. Push buttons are connected to PORTB (RB4-RB7). Pressing the keys will produce distinct patterns on LEDs connected to PORTC (RC0 and RC1).

4. Program to display a NAME on an LCD. LCD connections: RS -> RC3, EN -> RC0, LCD data lines -> PORTD (RD0 to RD7).

5. Program to add two numbers and display the result on an LCD. LCD connections: RS -> RC3, EN -> RC0, LCD data lines -> PORTD (RD0 to RD7).

6. Program to display data on an LCD using switches. If switch S1 is pressed, display the data on the LCD as "SET SPD: rpm". If switch S2 is pressed, increment the speed from 0 rpm to 1000. If switch S3 is pressed, decrement the speed. If switch S4 is pressed, display the speed as 1 rpm.

7. Generate PWM on RC2 and change the duty cycle in steps. PWM Frequency = 1KHZ with 10%, 50%, and 80% duty cycle. PWM period is specified by writing to the PR2 register, and PWM duty cycle is specified by writing to CCPR1L and CCP1CON<5:4>.

8. Generate PWM on RC2 and change the duty cycle when the key is pressed. If S1 (RB4) switch is pressed, increase the duty cycle by 5%, and if S2 (RB5) switch is pressed, decrease the duty cycle by 5%.

9. Read the analog voltage (0 to 5V) at RA0 pin and display the voltage value with respect to a 0 to 48V calibration.

10. Read the analog voltage (0 to 5V) at RA0 and generate a PWM pulse with respect to the ADC value. Display the ADC value on an LCD.

11. Communicate between two devices using UART serial communication.

12. Implement external interrupts and PORT change interrupts.

13. Implement timer interrupts using the timer preloading method and generate an accurate 1-second event using timer interrupts.
