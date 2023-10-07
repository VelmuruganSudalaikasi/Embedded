// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000

unsigned char Pwmhigh10, Pwmlow10, Pwmhigh50, Pwmlow50, Pwmhigh80, Pwmlow80;

void configuration(void);
void pwm_level(void);

void main() {
    configuration();
    while (1) {
        pwm_level();
    }
}

void configuration() {
    TRISC = 0xFB;      // setting rc2 as output mode 1111 1011
    PORTC=0x00;
    CCP1CON = 0x0C;    // setting pwm mode (PWM mode, single output)
    T2CON = 0x06;      // setting prescalar as 16
    PR2 = 0x5D;        // period register for desired PWM frequency (duty cycle)

    Pwmhigh10 = 0x09;
    Pwmlow10 = 0x20;
    Pwmhigh50 = 0x2F;
    Pwmlow50 = 0x00;
    Pwmhigh80 = 0x4B;
    Pwmlow80 = 0x00;
 
}

void pwm_level(void) {
    CCPR1L = Pwmhigh10;
    CCP1CON = (CCP1CON & 0xCF) | Pwmlow10;
    __delay_ms(3000);

    CCPR1L = Pwmhigh50;
    CCP1CON = (CCP1CON & 0xCF) | Pwmlow50;
    __delay_ms(3000);

    CCPR1L = Pwmhigh80;
    CCP1CON = (CCP1CON & 0xCF) | Pwmlow80;
    __delay_ms(3000);

}