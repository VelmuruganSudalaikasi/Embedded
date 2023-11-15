/*
 * File:   Keypad.c
 * Author: velmurugan
 *
 * Created on October 21, 2023, 7:45 PM
 */

// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#include "LCD.h"

#define _XTAL_FREQ 12000000     //Crystal Oscilator speed

void Configuration(void);       //initial port configuration

void Keypad_Scanning(void);     //Scanning the input from the user

void Standard_Scanning(void);

unsigned char result[] = ":PRESSED";    //Displaying the string

unsigned char temp;            //Variable for tracking the user pressed position

void main(void) {
    
    Lcd_Configuration();    //Configuring the LCD
    
    Configuration();
    
    while (1) {
    
        Keypad_Scanning();
   
    }
}

void Configuration(void) {
    
    TRISC = 0x00; //Direction as output
    
    TRISD = 0x00; //set the direction as the output for LCD data lines
    
    PORTD = 0X00;
    
    TRISB = 0xF0; //Set as direction of the ports
    
    PORTB = 0x00; //Set the 0's and 1's for the respective position
    
    PORTC = 0x00;

    //Lcd Configuration
    Lcd_Cmd(0x0C); //Display on cursor off
    
    __delay_ms(10);
    
    Lcd_Cmd(0x01); //clear the display;
    
    __delay_ms(10);
    
    Lcd_Cmd(0x38); //Selecting 5X7 dots
    
    __delay_ms(10);
    
    Lcd_Cmd(0x06); //Cursor Auto move
    
    __delay_ms(10);
    
    Lcd_Cmd(0x81); //Selecting the first row
    
    __delay_ms(10);
    
    for (char i = 0; i < 9; i++) {  //Iterate the Character by 
                                    //Character and sending to the LCD
        
        Lcd_Data(result[i]);
    
    }


}

void Keypad_Scanning(void) {    //Keypad_Scanning is polling method

    RB2 = 1, RB0 =RB1 = 0;      //Setting the col 1 bit and
                    //reading the value from the user action from row 1
    
    
    Lcd_Cmd(0x80);
  
    temp = PORTB;
    
    switch (temp & 0XF0) {    //Printing the respective character to the display
    
        case 0X10:
            Lcd_Data('1');
            break;
        
        case 0X20:
            Lcd_Data('4');
            break;
        
        case 0X40:
            Lcd_Data('7');
            break;
        
        case 0X80:
            Lcd_Data('*');
            break;

    }
    
    RB1 = 1, RB0 = RB2 = 0;   //setting the col2 as 1 and reading from the row2
    
    temp = PORTB;
    
    Lcd_Cmd(0x80);
    
    switch (temp & 0XF0) {  //Printing the respective character
        
        case 0X10:
            Lcd_Data('2');
            break;
            
        case 0X20:
            Lcd_Data('5');
            break;
            
        case 0X40:
            Lcd_Data('8');
            break;
            
        case 0X80:
            Lcd_Data('0');
            break;
 }
    
    RB0 = 1, RB2 = RB1 = 0; //Setting the col 3 as 1 and reading the 
                                //input from the row 3
    
    temp = PORTB;
    
    Lcd_Cmd(0x80);
    
   switch (temp & 0XF0) {
    
       case 0X10:
            Lcd_Data('3');
            break;
       
       case 0X20:
            Lcd_Data('6');
            break;
       
       case 0X40:
            Lcd_Data('9');
            break;
       
       case 0X80:
            Lcd_Data('#');
            break;

    }


}

