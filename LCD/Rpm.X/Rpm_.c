// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 600000

void Configuration(void);
void Lcd_displaydata(unsigned char);
void Lcd_instruction(unsigned char);
void Scanninginput(void);
void ContentPrint(void);
void Splitingcharacter(int);

char array[] = {"SET SPD:    RPM"}; // Text to be displayed on LCD
unsigned char input;
int i, speed = 0, d1, d2, d3, d4;

void main(){
    Configuration(); // Initialize the microcontroller and LCD configuration
   
    while(1)
    {
        Scanninginput(); // Scan input from PORTB and update speed value accordingly
        __delay_ms(1000); // Delay for 1 second
    }
}

void Configuration(){
    TRISC = 0x00; // Set all bits of PORTC as output (for LCD control signals)
    TRISD = 0x00; // Set all bits of PORTD as output (for LCD data signals)
    TRISB = 0xF0; // Set the upper 4 bits of PORTB as input and lower 4 bits as output
    PORTB = 0x00; // Initialize PORTB to 0
    PORTD = 0x00; // Initialize PORTD to 0
    OPTION_REG &= ~0x80; // Disable internal pull-up on PORTB
    Lcd_instruction(0x38); // Function set (2 lines, 5x8 character font)
    __delay_ms(100); // Delay for 1 second
    Lcd_instruction(0x08); // Display off
    __delay_ms(100); // Delay for 1 second
    Lcd_instruction(0x01); // Clear the display
    __delay_ms(100); // Delay for 1 second
    Lcd_instruction(0x06); // Entry mode set (right)
    __delay_ms(100); // Delay for 1 second
    Lcd_instruction(0x0C); // Display on and cursor off
    __delay_ms(100); // Delay for 1 second
}

void Lcd_instruction(unsigned char cmd){
    PORTC &= ~0x08; // Disable RS signal (RS = 0)
    PORTD = cmd; // Set the command to be executed
    PORTC |= 0x01; // Enable E signal (E = 1)
    PORTC &= ~0x01; // Disable E signal (E = 0)
    __delay_ms(1000); // Delay for 1 second
}

void Lcd_displaydata(unsigned char data){
    PORTC |= 0x08; // Enable RS signal (RS = 1)
    PORTD = data; // Set the data to be displayed
    PORTC |= 0x01; // Enable E signal (E = 1)
    PORTC &= ~0x01; // Disable E signal (E = 0)
    __delay_ms(1000); // Delay for 1 second
}

void Scanninginput(){
    input = PORTB; // Read input from PORTB
    
    switch(input){
        case 0xE0: 
            ContentPrint(); // Print the content on the LCD
        break;
        case 0xD0: 
            if(speed <= 49){
                speed++;
                Splitingcharacter(speed); // Update speed and print the value on the LCD
            }
        break;
        case 0xB0: 
            if(speed >= 1){
                speed--;
                Splitingcharacter(speed); // Update speed and print the value on the LCD
            }
        break;
        case 0x70: 
            speed = 0;
            Splitingcharacter(speed); // Set speed to 0 and print the value on the LCD
        break;
    }
}

void ContentPrint(){
    Lcd_instruction(0x80); // Set cursor to the beginning of the first line
    for(i = 0; i < 8; i++)
        Lcd_displaydata(array[i]); // Display the first part of the text
    for(; i < 12; i++)
        Lcd_displaydata('0'); // Display zeros for the speed value
    for(; i < 15; i++)
        Lcd_displaydata(array[i]); // Display the "RPM" part of the text
}

void Splitingcharacter(int speed){
    // Split the speed value into individual digits
    d1 = (speed / 1000); // Extract thousands digit
    d2 = ((speed - (1000 * d1)) / 100); // Extract hundreds digit
    d3 = ((speed - ((100 * d2) + (1000 * d1))) / 10); // Extract tens digit
    d4 = (speed - ((1000 * d1) + (100 * d2) + (10 * d3))); // Extract ones digit

    Lcd_instruction(0x88); // Set cursor to the second line at position 4
    Lcd_displaydata((unsigned char)(48 + d1)); // Display the thousands digit as character
    Lcd_displaydata((unsigned char)(48 + d2)); // Display the hundreds digit as character
    Lcd_displaydata((unsigned char)(48 + d3)); // Display the tens digit as character
    Lcd_displaydata((unsigned char)(48 + d4)); // Display the ones digit as character
}
