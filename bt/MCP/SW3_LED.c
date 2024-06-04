/****************************************************************/
/**
 *  file        main.c
 *  containts   Run application code
 */
/****************************************************************/

/****************************************************************/
/*  Includes section                                            */
/****************************************************************/
// #include
#include <stdio.h>

/****************************************************************/
/*  Types And Constants                                         */

/*PCC_PORTX*/
#define PCC 0x40065000
#define PORTA 0x124
#define PORTB 0x128
#define PORTC 0x12C
#define PORTD 0x130
#define PORTE 0x134

/*Base Address for PCR*/
#define BASE_PORTA 0x40049000
#define BASE_PORTB 0x4004A000
#define BASE_PORTC 0x4004B000
#define BASE_PORTD 0x4004C000
#define BASE_PORTE 0x4004D000

/*GPIOX*/
#define GPIOA 0x400FF000
#define GPIOB 0x400FF040
#define GPIOC 0x400FF080
#define GPIOD 0x400FF0C0
#define GPIOE 0x400FF100

#define PDOR 0X00
#define PSOR 0X04
#define PCOR 0X08
#define PTOR 0X0C
#define PDIR 0X10
#define PDDR 0X14
#define PIDR 0X18

/*SET OR CLEAR BIT*/
#define SET_BIT 1
#define CLEAR_BIT 0
/*PIN OF RGB LED*/
#define RED_LED 15
#define GREEN_LED 16
#define BLUE_LED 0

/****************************************************************/

/****************************************************************/
/*  Internal function prototype                                 */
/****************************************************************/
/*use to SET BIT or CLEAR BIT at n position*/
void f_BitMaskRevision(unsigned int *iAddress, unsigned char iPosition, unsigned char iAction);
/*Delay Function*/
void f_delay(unsigned short nSecond);
/*Configure Function*/
void f_ConfigureGPIO(unsigned int *PCC_PORTX, unsigned int *PORT_PCRn);
/*BLINK LED Function*/
void f_BlinkRedLed(void);
/*USE SW3 TO CONTROL REDLED*/
void f_Config_EN_DIS_LED(unsigned char cColor);
void EN_DIS_LED(unsigned char cColor);

/*USE SW2 (PORT C - PIN 12) to ENABLE RGB LED*/
void EN_RGBLED(unsigned int *GPIOD_PDOR);
/*USE SW3 (PORT C - PIN 13) to DISABLE RGB LED*/
void DIS_RGBLED(unsigned int *GPIOD_PDOR);

/*Read Bit*/
unsigned char ReadBit(unsigned int *Address, unsigned char nPos);

/*
********************************************************************************
PRACTICE 1: BIT MASK REVISION
********************************************************************************
Create a function to set or clear bit of a varible with below infor:
- Input:
    + Param 1: address of variable          (unsigned int*)
    + Param 2: position of bit              (unsigned char)
    + Param 3: action set or clear bit      (unsigned char)
- Output: the bit of variable is set or clear at input possition.

Note: Only set/clear indicated bit and do not impact on status of other bits.

********************************************************************************
Advance: Set/clear serial multi bits >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
********************************************************************************
*/

/*
********************************************************************************
PRACTICE 2: BLINK RED_LED - PTD15
********************************************************************************
The RED_LED is connected to PTD15, please configure the PTD15 pin to blink
the led.

Hint:
- Using function at "BIT MASK PRACTICE" to set/clear register value
- May be create 2 function, one for config, one for toggle  bit
********************************************************************************
Advance: >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
********************************************************************************
*/

/*
********************************************************************************
PRACTICE 3: USING SW3 TO ENABLE/DISABLE BLINK RED LED - PTD15
********************************************************************************
The SW3 button is connected to PTC13, please configure the PTC13 pin to detect
SW3 state then enable/disable blink the led.

Hint:
- Re-use PRACTICE 1 and 2
- Reading the value of Port Data Input Register (PDIR) of PORTC to detect state
- May create some macros for checking bit, state variable
********************************************************************************
Advance: >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
********************************************************************************
*/

/*
********************************************************************************
PRACTICE 4: USING SW2 and SW3 TO ENABLE/DISABLE BLINK RGB LED
********************************************************************************
The SW2, SW3 button is connected to PTC12, PTC13, please configure the PTC12 and
PTC13 pin to detect button state then enable/disable blink the RGB led.

Hint:
- Re-use PRACTICE 3
- PTC12 and PTC13 may be configured as button ISR
********************************************************************************
Advance: >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
********************************************************************************
*/

int main(void)
{
    f_Config_EN_DIS_LED(RED_LED);
    while (1)
    {
        EN_DIS_LED(RED_LED);
    }
}

/*
********************************************************************************
PRACTICE 1: BIT MASK REVISION
********************************************************************************

********************************************************************************
Advance: Set/clear serial multi bits >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
********************************************************************************
*/

void f_BitMaskRevision(unsigned int *iAddress, unsigned char iPosition, unsigned char iAction)
{
    if (iAction == 1)
    {
        *iAddress |= 1 << iPosition; /*Set bit at n Position = 1*/
    }
    else
    {
        *iAddress &= ~(1 << iPosition); /*Set bit at n Position = 0*/
    }
}

/*
********************************************************************************
PRACTICE 2: BLINK RED_LED - PTD15
********************************************************************************
********************************************************************************
Advance: >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
********************************************************************************
*/

/*USE RED LED (PORT D - PIN 15)*/
void f_BlinkRedLed(void)
{
    unsigned int *PCC_PORTD = (unsigned int *)(PCC + PORTD);
    unsigned int *PORT_PCR15 = (unsigned int *)(BASE_PORTD + 0x3C);
    unsigned int *GPIOD_PDOR = (unsigned int *)(GPIOD + PDOR);
    unsigned int *GPIOD_PDDR = (unsigned int *)(GPIOD + PDDR);

    f_ConfigureGPIO(PCC_PORTD, PORT_PCR15);
    f_BitMaskRevision(GPIOD_PDDR, 15, SET_BIT); /*SET DIRECTION as Output*/
    f_BitMaskRevision(GPIOD_PDOR, 15, CLEAR_BIT);
}

void f_ConfigureGPIO(unsigned int *PCC_PORTX, unsigned int *PORT_PCRn)
{
    /*Clock Enable*/
    f_BitMaskRevision(PCC_PORTX, 30, SET_BIT);
    /*Set pin as GPIO. PIN 10-9-8 AS 0-0-1*/
    f_BitMaskRevision(PORT_PCRn, 8, SET_BIT);
    f_BitMaskRevision(PORT_PCRn, 9, CLEAR_BIT);
    f_BitMaskRevision(PORT_PCRn, 10, CLEAR_BIT);
    /*DISABLE PULL-UP/PULL-DOWN*/
    f_BitMaskRevision(PORT_PCRn, 1, CLEAR_BIT); /*PORT_PCRn.PE - Pull Enable*/
    f_BitMaskRevision(PORT_PCRn, 0, CLEAR_BIT); /*PORT_PCRn.PS - Pull Disable*/
}

/*
********************************************************************************
PRACTICE 3: USING SW3 TO ENABLE/DISABLE BLINK RED LED - PTD15
********************************************************************************
********************************************************************************
Advance: >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
********************************************************************************
*/

/*USE SW3 (PORT C - PIN 13) to EN/DIS RED LED*/
void f_Config_EN_DIS_LED(unsigned char cColor)
{
    unsigned int *PCC_PORTD = (unsigned int *)(PCC + PORTD);
    unsigned int *PORT_PCR15 = (unsigned int *)(BASE_PORTD + 0x3C);
    unsigned int *PORT_PCR16 = (unsigned int *)(BASE_PORTD + 0x40);
    unsigned int *PORT_PCR0 = (unsigned int *)(BASE_PORTD + 0x00);
    unsigned int *GPIOD_PDOR = (unsigned int *)(GPIOD + PDOR);
    unsigned int *GPIOD_PDDR = (unsigned int *)(GPIOD + PDDR);
    unsigned int *PCC_PORTC = (unsigned int *)(PCC + PORTC);
    unsigned int *PORT_PCR13 = (unsigned int *)(BASE_PORTC + 0X34);
    unsigned int *GPIOC_PDDR = (unsigned int *)(GPIOC + PDDR);
    /*unsigned int* GPIOC_PDIR = (unsigned int*) (GPIOC + PDIR);*/

    /*Config GPIO Output*/
    switch (cColor)
    {
    case RED_LED:
        f_ConfigureGPIO(PCC_PORTD, PORT_PCR15);
        break;
    case GREEN_LED:
        f_ConfigureGPIO(PCC_PORTD, PORT_PCR16);
        break;
    case BLUE_LED:
        f_ConfigureGPIO(PCC_PORTD, PORT_PCR0);
        break;
    default:
        break;
    }

    f_BitMaskRevision(GPIOD_PDDR, cColor, SET_BIT); /*SET DIRECTION as Output*/
    f_BitMaskRevision(GPIOD_PDOR, cColor, SET_BIT); /*use to turn off led at the first time set up*/
    /*Config GPIO input*/
    f_ConfigureGPIO(PCC_PORTC, PORT_PCR13);
    /*Set Input*/
    f_BitMaskRevision(GPIOC_PDDR, 13, CLEAR_BIT); /*SET PORT D PIN 13 as Input*/
                                                  /*if(ReadBit(GPIOC_PDIR,13) == 1) f_BitMaskRevision(GPIOD_PDOR,15,CLEAR_BIT);
                                                  else f_BitMaskRevision(GPIOD_PDOR,15,SET_BIT);*/
}

void EN_DIS_LED(unsigned char cColor)
{
    unsigned int *GPIOD_PDOR = (unsigned int *)(GPIOD + PDOR);
    unsigned int *GPIOC_PDIR = (unsigned int *)(GPIOC + PDIR);
    if (ReadBit(GPIOC_PDIR, 13) == 1)
        f_BitMaskRevision(GPIOD_PDOR, cColor, CLEAR_BIT);
    else
        f_BitMaskRevision(GPIOD_PDOR, cColor, SET_BIT);
}

/*Read Bit to return value of bit is 0 or 1*/
unsigned char ReadBit(unsigned int *Address, unsigned char nPos)
{
    unsigned int iTemp;
    iTemp = *Address & (1 << nPos);
    if (iTemp != 0)
        return 1;
    else
        return 0;
}
