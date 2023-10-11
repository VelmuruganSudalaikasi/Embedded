
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
unsigned char* dir_b=(unsigned char*)0x86,*dir_c=(unsigned char*)0x87,*op_reg=(unsigned char*)0x81; 
unsigned char* data_b=(unsigned char*)0x06,*data_c=(unsigned char*)0x07;       /*mapping the register address to
                                                                                * pointer variable to reference the address 
                                                                                */                            
unsigned char val;
void main(){
    *dir_b=0xF0;   //Deference the pointer and assign the value to respective register 
    *dir_c=0x00;
    *data_b=0x00;
    *data_c=0x00;
    *op_reg&=0x7F;   //Activating the internal pull up register
    while(1){
        val=*data_b;    //Reading the value in portb register
        switch(val){
            case 0xE0: *data_c=0x30; break;      //Based on the condition we blink the led
            case 0xD0: *data_c=0x10; break;
            case 0xB0: *data_c=0x20; break;
            case 0x70: *data_c=0x00; break;
            default:
                *data_c=0x00;
        
        }
    
        
        
    }
    
    
    
}