
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
#define _XTAL_FREQ 6000000 //csrystal oscilator speed
void init(void); // initial configuration 
void Lcd_cmd(unsigned char); // 
void Lcd_data(unsigned char);  //
void TX_Scanning(void);
void RX_Scanning(void);
unsigned char result;
unsigned char value;
void main(){
    init();
    while(1){
    TX_Scanning();
    RX_Scanning();
    
    }
}
//initial configuration 
void init(){
    TRISD=0x00; //configure the output direction
    TRISB=0xF0; //all pins are output mode
    PORTB=0x00;
    PORTD=0x00;
    PORTC=0x00;
    
    
    OPTION_REG&=0x7F;
    //configure the uart port RC6->TX, RC7->RX
    TRISC=0x80;
    //uart configuration
    TXSTA=0x20;
    RCSTA=0x90;
    SPBRG=0x09; //9600 baud rate low speed
    //configuration of LCD enable,RS,Read/write,d0...d7
    
    Lcd_cmd(0x38); // 2 lines, 5X10 dots
    __delay_ms(100);
    Lcd_cmd(0x38);//clear the display
    __delay_ms(100);
    Lcd_cmd(0x06); //entry mode set
    __delay_ms(100);
    Lcd_cmd(0x0C); //turn on the display
    __delay_ms(100);
    Lcd_cmd(0x80);   //postion selection
    __delay_ms(100);
    Lcd_data('T');
    Lcd_data('X');
    Lcd_data(':');
    Lcd_cmd(0xC0); //2 row 1 col
    Lcd_data('R');
    Lcd_data('X');
    Lcd_data(':');
               
}
void TX_Scanning(void){
    value=PORTB;
    Lcd_cmd(0x83);
    switch(value){
        case 0xE0:
            TXREG='A';
            Lcd_data('A'); //displaying the A
            __delay_ms(100);
            break;
        case 0xD0:
            TXREG='B';
            Lcd_data('B'); //displaying the B
            __delay_ms(100);
            break;
        case 0xB0:    
        TXREG='C';
        Lcd_data('C');//displaying the C
            __delay_ms(100);
            break;
        case 0x70:
            TXREG='D';
            Lcd_data('D');//Displaying the D
            __delay_ms(100);
            break;
            
    }
    
}
void RX_Scanning(void){
    
    if(RCIF==1){
        result=RCREG;
        Lcd_cmd(0xC3); //pointing the position
        switch(result){
            case 'a': Lcd_data('a');__delay_ms(100); break;
            case 'b': Lcd_data('b');__delay_ms(100); break;
            case 'c': Lcd_data('c');__delay_ms(100); break;
            case 'd': Lcd_data('d');__delay_ms(100); break;
        }
        
        RCIF=0;
    }

}

//choose the rs as portb 0 pin
void Lcd_cmd(unsigned char cmd){
    PORTC &=~0x01; //RS 0 for command
    PORTD =cmd;
    PORTC |=0x02; //EN =1
    PORTC &=~0x02; //EN=0
    __delay_ms(100); 
}
void Lcd_data(unsigned char data){
    PORTC |=0x01; //RS 1 for data
    PORTD=data;
    PORTC |=0x02;  //En as 1
    PORTC &=~0x02;  //En as 0
    __delay_ms(100); 
}