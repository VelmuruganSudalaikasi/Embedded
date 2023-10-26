/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: velmurugan
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_H
#define	LCD_H


void Lcd_Data(unsigned char);   //Sending data to the LCD

void Lcd_Cmd(unsigned char);    //Sending command to the LCD

void Lcd_Configuration(void);       //Configuring the LCD

void Lcd_Print(unsigned char*);     //Display print

 void Lcd_Print(unsigned char* x){    //Printing the Data on LCD

    while(*x){
        Lcd_Data(*x);
        x++;
    }
}

//initial Configuration 
 
void Lcd_Configuration()
{
    TRISD=0x00;
    
    PORTD=0x00;
    
    TRISC=(TRISC&0x3F);
    
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
    
    
 }

//Write the Data to the LCD by character by character

void Lcd_Data(unsigned char data) {
    //enable bit RC7
    //RS bit RC6;
    
    PORTD = data; //Load the register with character
    
    PORTC |= 0x40;
    
    PORTC |= 0x80;
    
    PORTC &= ~0x80;
    
    __delay_ms(10);


}

//Sending the Instruction to the LCD

void Lcd_Cmd(unsigned char cmd) {
 
    PORTD = cmd; //Load the register with character
    
    PORTC &= ~0x40;
    
    
    PORTC |= 0x80;
    
    PORTC &= ~0x80;
    
    __delay_ms(10);

}
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

