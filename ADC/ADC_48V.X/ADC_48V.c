
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
void Configuration(void);
void Lcd_command(unsigned char);
void Lcd_display(unsigned char);
void Lcd_printing(unsigned int);
unsigned int value_msb,value_lsb,value,result;

void main(){
   Configuration(); //Initial configuration 

   while(1){
       
   Lcd_command(0x80); //Selecting the position from the display
   
   ADCON0|=0x04;    // Purpose of R3 bit for tracking the ADC 
   while(ADCON0 & 0x04); //This loop wait until the ADC done
   value_msb=ADRESH;     //Reading the value in register
   value_lsb=ADRESL;     //Reading the register
   value= (value_msb<<8)+ (value_lsb); //2 bit + 8 bit =>10 bit 
   result=(((float)value/1023)*48);        //Converting to 48 value
   Lcd_printing(result);         //Sending the value to the display
   __delay_ms(100);
   
   }
  
}
void Configuration(void){
    TRISD=0x00; 
    TRISC=0x00;
    PORTC=0x00;
    PORTD=0x00;
    TRISA=0x01;
    ADCON0=0x81;    // 100000-1 LSB TO MSB (1 TURN ON THE MODULE,- UNIMPLEMENTED,2ND RESET BIT FOR A/D PROCESS,000 SELECTING THE AN0,00 FOR FOSOC) 
    ADCON1=0x8E;    //10--0000 //LSB 000 port configuration MSB 1 FOR RIGHT JUSTIFIED,6 th bit using for Fosoc selecting 
    Lcd_command(0x38); //Selecting the 5X7 and 16 X 2 display 
   __delay_ms(100);
   Lcd_command(0x01); //Clearing the display
   __delay_ms(100);
   Lcd_command(0x06); //Setting the R->L cursor move
   __delay_ms(100);
   Lcd_command(0x0C); //display on cursor off
   __delay_ms(100);
   
}
void Lcd_command(unsigned char cmd){ //This function used to execute the predefined commands
    
    PORTC &=~0x08;
    PORTD=cmd;
    PORTC |=0x01;
    PORTC &=~0x01;
    __delay_ms(100);
    
}
void Lcd_display(unsigned char data){ //This function help to print the data on LCD
    PORTC |=0x08;
    PORTD=data;
    PORTC |=0x01;
    PORTC &=~0x01;
    __delay_ms(100);

}

void Lcd_printing(unsigned int  value){
    unsigned int space[3]={0,0,0};
    int temp=0;
    while(value!=0){           //Split the value one by one and add to the array
        space[temp]=(value%10);
        temp=temp+1;
        value/=10;
        
    }
    for(int i=2;i>=0;i--){      //Sending the value to the display one by one 
        Lcd_display((unsigned char)space[i]+48);
        
    }Lcd_display('V');
}