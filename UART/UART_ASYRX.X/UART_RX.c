
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
#define _XTAL_FREQ 6000000 //crystal oscillator

void init(void);
void RT_Scanning(void);
unsigned char result;

void main(){
    init(); //initial configuration
    while(1){
    RT_Scanning();
    }
}
void init(void){
    TRISB=0x80;// RC6 AS RX RC7 AS TX
    PORTB=0x00;
    TRISC=0x80; //RC7->TX,RC
    PORTB=0x00;
    //UART Configuration
    TXSTA=0x20;
    RCSTA=0x90;
    SPBRG=0x09; //low speed baud rate
}
void RT_Scanning(void){
    if(RCIF==1){
    result=RCREG;
    switch(result){
      case 'A': TXREG='a'; __delay_ms(100); break;
      case 'B': TXREG='b'; __delay_ms(100); break;
      case 'C': TXREG='c'; __delay_ms(100); break;
      case 'D': TXREG='d'; __delay_ms(100); break;
    }RCIF=0; //clear the bit by software
    }
}