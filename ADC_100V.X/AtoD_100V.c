
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
void Configuration(void); //Prototype
void Lcd_displaydata(unsigned char);//Prototype
void Lcd_command(unsigned char); //Prototype
void Lcd_printing(unsigned int); //Prototype
unsigned int High,Low,Result; //Global variables
void main(){
    Configuration();   //Initialize the LCD,ADC

    while(1){ 
        Lcd_command(0x80); //Cursor position  
        ADCON0|=0x04;      //set the bit 3rd bit for A to D conversion wait
        while(ADCON0&0x04); //Waiting for Hardware Reset of 3rd bit(Indication of ADC done)
        High=ADRESH;        //Reading the MSB 8 bits
        Low=ADRESL;         //Reading the LSB 2 bits
        Result=(High<<2)+ (Low>>6);  //8+2=>10 bits
        Result=((float)Result/1023)*100; //Converting to the 100
        Lcd_printing(Result);         //Sending the Result to the Printing purpose
        __delay_ms(100);
    }
}


void Configuration(void){
    TRISA=0x04; //setting R2 as input
    TRISC=0x00; //Set PORTC all Register as output mode
    TRISD=0x00; //Set PORTD all Register as output mode
    ADCON0=0x91; //100100-1 (LSB-MSB 1st bit Turn on the analog module, unimplemented, selecting AN2 channel,Fosoc 32)
    ADCON1=0x02; //00--0010 (1-3 bit for selecting AN2 config ,6 for Fosc,7 for left justified )
    Lcd_command(0x38);
    __delay_ms(100);
     Lcd_command(0x01);
    __delay_ms(100);
     Lcd_command(0x06);
    __delay_ms(100);
     Lcd_command(0x0C);
    __delay_ms(100);
    Lcd_displaydata(0x80);
    
    
   
}
void Lcd_displaydata(unsigned char data){
    PORTC |=0x08;
    PORTD=data;
    PORTC |=0x01;
    PORTC &=~0x01;
    __delay_ms(100);
}
void Lcd_command(unsigned char cmd){
    PORTC &=~0x08;
    PORTD=cmd;
    PORTC |=0x01;
    PORTC &=~0x01;
    __delay_ms(100);

}
void Lcd_printing(unsigned int  value){
    unsigned char space[3]="000";
    int temp=0;
    while(value!=0){           //Split the value one by one and add to the array
        space[temp]=48+(value%10);
        temp=temp+1;
        value/=10;
        
    }
    for(int i=2;i>=0;i--){      //Sending the value to the display one by one 
        Lcd_displaydata(space[i]);
        
    }Lcd_displaydata('V');
}