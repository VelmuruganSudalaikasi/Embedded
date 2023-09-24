
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
void Lcd_command(unsigned char);
void Lcd_data(unsigned char);
void initi(void);
char name[50]={"VELMURUGAN"};
unsigned char i;
int k;
void main(){
       initi();//calling the initi function
     Lcd_command(0x84);// specific location
     for(k=0;k<10;k++){ //Looping the character one by one and sent to lcd with                
         Lcd_data(name[k]);// data Left to Right
     } 
     Lcd_command(0x04);// Right to left specific command   
     Lcd_command(0xCE);//specific location
     for(k=0;k<10;k++){ //Looping the character Right to left
       Lcd_data(name[k]);// character right to left
    }    
    while(1);
       }
void initi(){
    TRISC=0x00;//setting all the pin of c as output 
    TRISD=0x00;// setting all the pin of d as output
    PORTC=0x00; 
    PORTD=0x00;
Lcd_command(0x38);//Function set
__delay_ms(100);
Lcd_command(0x08);//display off
__delay_ms(100);
Lcd_command(0x01);//clear display
__delay_ms(100);
Lcd_command(0x06);//entry mode set cursor position left or right
__delay_ms(100);   
Lcd_command(0x0C);//display on and cursor on
__delay_ms(100);

          }
void Lcd_command(unsigned char i){ //used to configure the display
    PORTC &=~0x08;
    PORTD=i;
    PORTC|=0x01;
    PORTC &=~0x01;
    __delay_ms(100);
    
}
void Lcd_data(unsigned char i){  //used to print the data 
    PORTC |=0x08;
    PORTD=i;
    PORTC|=0x01;
    PORTC&=~0x01;
    __delay_ms(100);
    
}   