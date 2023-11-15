#include<xc.h>
#define _XTAL_FREQ 16000000


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

