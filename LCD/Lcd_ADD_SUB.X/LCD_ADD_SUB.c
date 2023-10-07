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
#define _XTAL_FREQ 600000
void Configuration(void);               //This function does the initial configuration
void Lcd_displaydata(unsigned char);    //This function display the data
void Lcd_instruction(unsigned char);    //This function executes the predefined commands
void WriteFunction(int);                //This function sent the data to lcd with help of lcd_display data
void Atoi(int);                         //This Function convert the int to char 
unsigned char array[10],plus='+',minus='-',equals='=',zero='0';                //This array used to store the char 
int Firstnumber=200,Secondnumber=2000,i,j,result;
void main(){
    Configuration();                //function call 
    Lcd_instruction(0x80);          //Specify the position
    Atoi(Firstnumber);              //Atoi convert the int to char

    Lcd_displaydata(minus);         //'-' Printing the minus  
             
    Atoi(Secondnumber);              //Atoi convert the int to char
    result=Firstnumber-Secondnumber;
    Lcd_displaydata('=');            //Printing the equals
    if(result>0){ Lcd_displaydata(plus);}                   // Handling the -,+,0 based on result
    else if(result!=0){Lcd_displaydata(minus); result*=-1;}
    else Lcd_displaydata('0');
  
    Atoi(result);
  
    while(1);
    
} 
void Configuration(){
    TRISC=0x00;                 // Set PORTC as output (for LCD control signals)
    TRISD=0x00;                 // Set PORTD as output (for LCD data signals)
    
    Lcd_instruction(0x38);      // Function set (2 lines, 5x8 character font)
    __delay_ms(1000);
    Lcd_instruction(0x08);      // Display off
    __delay_ms(1000);
    Lcd_instruction(0x01);      // Clear display
    __delay_ms(1000);
    Lcd_instruction(0x06);      // Entry mode set as right (increment cursor)
    __delay_ms(1000);
    Lcd_instruction(0x0C);      // Display on and cursor off
    __delay_ms(1000);
}

void Lcd_displaydata(unsigned char data){ //This function sends the data to the display
    PORTC|=0x08;                // Enable RS signal (RS = 1)
    PORTD=data;                 // Set the data to be displayed
    PORTC|=0x01;                // Enable E signal (E = 1)
    PORTC&=~0x01;               // Disable E signal (E = 0)
    __delay_ms(1000);           // Delay for display stability
}

void Lcd_instruction(unsigned char cmd){ //This function sends the command the display
    PORTC&=~0x08;               // Disable RS signal (RS = 0)
    PORTD=cmd;                  // Set the command to be executed
    PORTC|=0x01;                // Enable E signal (E = 1)
    PORTC&=~0x01;               // Disable E signal (E = 0)
    __delay_ms(1000);           // Delay for display stability
}

void Atoi(int number){              //Convert the int to char and store the character to the array
    int temp=number;
    i=0;
    while(temp){
        number=temp%10;
        array[i++]=(unsigned char)number+48;  // Convert digit to ASCII character and store in the array
        temp/=10;                             // Move to the next digit
    }
    i--;
    WriteFunction(i);                         //Calling the WriteFuncation to display the number on the LCD
}

void WriteFunction(int j){     //This Function iterate the array elements one by one and sent to the display data 
    for(;j>=0;j--)
        Lcd_displaydata(array[j]);
}
