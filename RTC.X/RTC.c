
#include <xc.h>

#define XTAL_FREQ 20000000

#include "Config.h"

#include "I2C.h"

#include "LCD.h"

#include "RTC.h"

#define Device_add 0xD0

#define Reg_add  0x00

unsigned char Time[6]="TIME:";

unsigned char DATE[6]="DATE:";

unsigned char Mode='P';

unsigned char Hour=8;

unsigned char Min=55;

unsigned char Sec=33;

unsigned char Day=3;

unsigned char Month=12;

unsigned char Year=30;

unsigned char Date=22;




void main(void) {
     
    //I2C configuration and Writing Sequence
    
    I2C_Master_Init();
    
    I2C_Start();        
    
    Set_Time_Calender(Sec,Min,Mode,Hour,Day,Month,Year,Date);
    
    I2C_Stop();
    
    //Writing Sequence  and Lcd Configuration
    
    Lcd_Configuration();
    
    Lcd_Cmd(0x80);
    
    Lcd_Print(Time);
    
    Lcd_Cmd(0xC0);
   
    Lcd_Print(DATE);
    
    //Read Sequence
    
    
    while(1){
      
    I2C_Start();
    
    I2C_Device_Select_R((unsigned char)0xD0 ,(unsigned char) 0x00);
    
    Read_Time();
    
    Read_Date();
    
    I2C_Stop();
    
    
    Lcd_Cmd(0x85);
    
    Lcd_Print(Current_Time);
    
    Lcd_Cmd(0xC5);
    
    Lcd_Print(Current_Date);
     
    
    }
    

}

