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
 * Author: 
 * Comments:Hello it's me
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef I2C_H
#define	I2C_H



  //Write Sequence

//Function Proto types 

void I2C_Start(void);   //Start the Communication

void I2C_Wait(void);    //Monitoring the idle state of wire

void I2C_Stop(void);     //Terminate the connection

void I2C_ACK(void);      //Master Acknowledgment

void I2C_Repeat_Start(void);  //Repeated start for bus holding

int I2C_Write_Data(unsigned char);  //Write the character to Respective location

void I2C_NACK(void);       //Master Negative-Acknowledgment

void I2C_Master_Init(void);  //Initial configuration for Master

unsigned char I2C_Read_Data(int );  //Read the Data from the Respective Location

void  I2C_Page_Read(unsigned char*,int,unsigned char ,unsigned char );    
//Read the Sequence of Byte

 void I2C_Page_Write(unsigned char *,unsigned char ,unsigned char );     
 //Write the Sequence of Byte



   
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    
void I2C_Start(void);

void I2C_Wait(void);

void I2C_Stop(void);

void I2C_Master_RCEN(void);

void I2C_ACK(void);

void I2C_Repeat_Start(void);

int I2C_Write_Data(unsigned char);

void I2C_NACK(void);

void I2C_Master_Init(void);

unsigned char I2C_Read_Data(int );

void  I2C_Page_Read(unsigned char*,int,unsigned char ,unsigned char );

 void I2C_Page_Write(unsigned char *,unsigned char ,unsigned char );


 

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

