//This is implementation of I2C Read and write to EEPROM

#define _XTAL_FREQ 16000000     //Clock Frequency

#include "Config.h"            //Includes the Configuration bits

#include "I2C.h"               //Includes the I2C API's

#include "LCD.h"               //Includes the LCD API's

#define Device_add 0xA0        //Device Addresss

#define Reg_add  0x0020        //Register Addresss

#define READ_BYTE_SIZE 3       //Read BYTE SIZE 

unsigned char Read[]="READ:";  //Characters for LCD Display

unsigned char Write[]="Write:"; //Characters for LCD Display

unsigned char Word[]="I2C";    //Actual Write character Sequence

unsigned char  result[READ_BYTE_SIZE];  //Array for Read-> Store
 
void main(){
    
   //Lcd configuration and printing dummy string
   
    Lcd_Configuration();            //LCD configuration
    
    Lcd_Cmd(0x80);                  //Pointing row->0,col->0
    
    Lcd_Print(Read);                //Iterate Read array characters and displaying in LCD
    
    Lcd_Cmd(0xC0);                  //Pointing row->1,col->0
    
    Lcd_Print(Write);               //Iterate the Characters and displaying in LCD
    
    //I2C configuration
    
    I2C_Master_Init();              //Initial Configuration of I2C Master 
    
    //Reading Sequence
    
    Lcd_Cmd(0x80+6);               //Pointing to row->0,col->6
    
    Lcd_Print(Word);              //Printing the Character on LCD
    
    I2C_Start();                 //Initiate the I2C Communication by SDL low while SCL high
    
    I2C_Page_Write(Word,Device_add,Reg_add);  //Page write function Write the content which inside the Word array location of Device and Reg address
    
    I2C_Stop();                    //Terminate the I2C by SDL low->high while SCL is high                                 
    
    __delay_ms(100);           
    
   //Writing Sequence
    
    I2C_Start();                         //Initiate the Communication 
    
    I2C_Page_Read(result,READ_BYTE_SIZE-1,Device_add,Reg_add);  //Used to Read the contents in the Device_add of Reg_Add
    
    I2C_Stop();                             //Terminate the Connection
    
    Lcd_Cmd(0xC6);                          //Pointing to row->1,col->6 location
   
    //Printing to the LCD
    
    Lcd_Print(result);                    //Printing the Result with the help of LCD
    
    while(1);

}