#include<xc.h> 
#define I2C_BAUDRATE 100000 
#define _XTAL_FREQ 16000000

//Sequence write
  unsigned char buff;                                  //Temp buff
 
//notice the IDLE

void I2C_Wait(){

while(READ_WRITE || SSPCON2&0X1F);

}


 //Initiate the Communication

void I2C_Start(){

I2C_Wait();

SEN=1;

}

//Terminate the Communication

void I2C_Stop(){

I2C_Wait();

PEN=1;

}

//Repeated_Start 

void I2C_Repeat_Start(){

I2C_Wait();

RSEN=1;

}

//Initial Configuration of Master Node

void I2C_Master_Init(){

TRISC3=1;

TRISC4=1; //SCL,SDL

SMP=1; //for 100 khz //SSPSTAT 7 bit for slew rate

CKE=0; //For disable the SMBUS standard (System management bus)

SSPEN=1;//bit 5 enable the I2c serial communication

SSPCON|=0X08; //Enable the I2C 7-bit address start and stop and interrupt enable

SSPADD=((_XTAL_FREQ)/(4*I2C_BAUDRATE))-1;

}



//Master Receiver mode only

void I2C_ACK(){

	ACKDT=0;  //ACK

	I2C_Wait();

    ACKEN=1;  //Send the Signal

}

//Master Receiver mode only


void I2C_NACK(){

 ACKDT=1;  //NACK

 I2C_Wait();

 ACKEN=1; //Send the signal


}

//Writing the Character

int I2C_Write_Data(unsigned char data){

	I2C_Wait();

	SSPBUF=data;

	I2C_Wait();

  return (int)ACKSTAT;
}

//Reading the Character

unsigned char I2C_Read_Data(int flag){
  
  I2C_Wait();
  
  RCEN=1;
  
  I2C_Wait();
    
   while(!SSPIF);
  
  buff=SSPBUF;
  
  SSPIF=0;
  
  (flag!=0)?I2C_ACK():I2C_NACK();

  return buff;
}

void I2C_Page_Write(unsigned char *data,unsigned char Device_add,
         unsigned char Reg_add){
 
  while(I2C_Write_Data((Device_add & 0xFE))){
 
      I2C_Repeat_Start();
  
  }

  I2C_Write_Data(Reg_add>>8);
  
  I2C_Write_Data((unsigned char)Reg_add);
 
  while(*data){
  
      I2C_Write_Data(*data);
      
       data++;
  
  }
  __delay_ms(10);
  
  }
  
  //Read Sequence
  
  void  I2C_Page_Read(unsigned char* result,int Size,
        unsigned char Device_add,unsigned char Reg_add){
          
  while(I2C_Write_Data(Device_add & 0xFE)){
      I2C_Repeat_Start();
      
  }
  
  I2C_Write_Data(Reg_add>>8);
  
  I2C_Write_Data((unsigned char)Reg_add);
 
     
  I2C_Repeat_Start();
   
  while(I2C_Write_Data(Device_add | 0x01))
      I2C_Repeat_Start();
 
  
  for(int i=Size;i>=0;i--)
  {
      
      result[Size-i]=(unsigned char)I2C_Read_Data(i);
  }
  
  result[Size+1]=0;
  
 
  }
  
  
 