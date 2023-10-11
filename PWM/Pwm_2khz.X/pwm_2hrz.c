
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

void configuration(void);

char pwmh20,pwml20,pwmh40,pwml40,pwmh90,pwml90; 

void pwm_change(void);

void main(void){

    configuration();//Initial configuration 
 
    while(1){
    
        pwm_change(); //This function changing the pwm
    } 

}
void configuration(void){
    TRISC=0xFD; //RC1 AS OUTPUT 11111101
    PORTC=0x00; //setting output
    CCP2CON=0x0C; //set as 00001100 as PWM mode
    PR2=0x2E; // period cycle register
    T2CON=0x06; //timer2 control register
    
    pwmh20=0x09; //setting the duty cycle(20%) first 8 bits 
    pwml20=0x20; //setting the LSB 2 bit of duty cycle.
    pwmh40=0x1C; //setting the duty cycle(40%) first 8 bits
    pwml40=0x20; //setting the LSB for (40%) 2 bits
    pwmh90=0x2A; //setting the duty cycle (60%) first 8 bits
    pwml90=0x10; //setting the LSB for (60%) 2 bits
    
   
    

}

void pwm_change(void){
    CCPR2L=pwmh20; // Assign the 20% duty cycle value for the register
    CCP2CON=(CCP2CON&0x0F)|pwml20;// Assign the 20% duty cycle LSB for the register
    __delay_ms(3000);  //Adding delay 

    CCPR2L=pwmh40;     //Assign the 40% duty cycle value for the register
    CCP2CON=(CCP2CON&0x0F)|pwml40; //Assign the 40% duty cycle LSB for the register
    __delay_ms(3000); //Adding delay

    CCPR2L=pwmh90; //Assign the 90% duty cycle value f  or the register
    CCP2CON=(CCP2CON&0x0F)|pwml90;//Assign the 90% duty cycle LSB for the register
    __delay_ms(3000);// Adding delay/


    
    
}