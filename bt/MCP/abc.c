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
#include "SK32144_Address.h"

/****************************************************************/
/*  Types And Constants                                         */

/*SET OR CLEAR BIT*/
#define SET_BIT 1
#define CLEAR_BIT 0
/*PIN OF RGB LED*/
#define RED_LED 15
#define GREEN_LED 16
#define BLUE_LED 0

/*Interrupt MODE*/
#define LOGIC0 0x8
#define RISING_EGDE 0x9
#define FALLING_EGDE 0xA
#define EITHER_EGDE 0xB
#define LOGIC1 0xC

/*NVIC_ISER 0-7*/
#define NVIC_ISER 0xE000E100

/*LED MODE*/
#define HIGH 1
#define LOW 0

/****************************************************************/

/****************************************************************/
/*  Internal function prototype                                 */
/****************************************************************/
/*use to SET 1 BIT or CLEAR BIT at n position*/
void f_BitMaskRevision(unsigned int *reg, unsigned char position, unsigned char action);
/*use to SET Multibit BIT or CLEAR BIT at n position*/
void f_SetMultibit(unsigned int *reg, unsigned char position, unsigned int mask, unsigned int value);
/*Delay Function*/
void f_delay(unsigned int second);
/*Configure Function*/
void f_ConfigureGPIO(unsigned int *pcc_portx, unsigned int *port_pcrn);
/*BLINK LED Function*/
void f_BlinkRedLed(void);
/*USE SW3 TO CONTROL REDLED*/
void f_Config_EN_DIS_LED(unsigned char color);
void EN_DIS_LED(unsigned char color);

/*USE SW2 (PORT C - PIN 12) to ENABLE RGB LED*/
void EN_RGBLED(unsigned int *gpiod_pdor);
/*USE SW3 (PORT C - PIN 13) to DISABLE RGB LED*/
void DIS_RGBLED(unsigned int *gpiod_pdor);

/*Read Bit*/
unsigned char ReadBit(unsigned int *reg, unsigned char position);

/*Config GPIO input, Interrupt mode*/
void f_ConfigInterrupt(unsigned int *port_pcrn, unsigned char mode);
/*Config ISER*/
void f_ConfigNVIC(unsigned char id);
/*HANDlER*/
void PORTC_IRQHandler(void);

/*Control color of LED and MODE(HIGH or LOW)*/
void Active_LED(unsigned char color, unsigned char mode);

/*Return 1 is SW2 ON, Return 1 when SW3 ON or default*/
unsigned char SwitchStatus(void);

unsigned char f_FindPinISF(unsigned int *portx_isf);

void Blink_RGBLED(void);

void TurnOFF_RGBLed(void);

/************************GLOBAL VARIABLE*********************************/
static unsigned char g_mode = 0;

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
    unsigned int *pcc_portc = (unsigned int *)(PCC + PORTC);
    unsigned int *portc_pcr12 = (unsigned int *)(BASE_PORTC + 0x30);
    unsigned int *portc_pcr13 = (unsigned int *)(BASE_PORTC + 0x34);
    unsigned int *gpioc_pddr = (unsigned int *)(GPIOC + PDDR);

    /*Enable Clock, Configure GPIO mode, Disable pull resistor*/
    f_ConfigureGPIO(pcc_portc, portc_pcr12);
    f_ConfigureGPIO(pcc_portc, portc_pcr13);
    f_Config_EN_DIS_LED(RED_LED);
    f_Config_EN_DIS_LED(GREEN_LED);
    f_Config_EN_DIS_LED(BLUE_LED);
    /*Config Interrupt for PORT C*/
    f_ConfigInterrupt(portc_pcr12, RISING_EGDE);
    f_ConfigInterrupt(portc_pcr13, RISING_EGDE);
    /*Set PDDR input for pin 12-13 PORT*/
    f_BitMaskRevision(gpioc_pddr, 12, CLEAR_BIT);
    f_BitMaskRevision(gpioc_pddr, 13, CLEAR_BIT);
    /*Config ISER for PORT C (id 61)*/

    f_ConfigNVIC(61);

    while (1)
    {
        if (g_mode == 1)
        {
            Blink_RGBLED();
        }
        else if (g_mode == 2)
        {
            TurnOFF_RGBLed();
        }
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

void f_BitMaskRevision(unsigned int *reg, unsigned char position, unsigned char action)
{
    if (action == 1)
    {
        *reg |= 1 << position; /*Set bit at n Position = 1*/
    }
    else
    {
        *reg &= ~(1 << position); /*Set bit at n Position = 0*/
    }
}

void f_SetMultibit(unsigned int *reg, unsigned char position, unsigned int mask, unsigned int value)
{
    unsigned int temp = *reg;
    temp &= ~(mask << position);
    temp |= (value << position);
    *reg = temp;
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
    unsigned int *pcc_portd = (unsigned int *)(PCC + PORTD);
    unsigned int *portd_pcr15 = (unsigned int *)(BASE_PORTD + 0x3C);
    unsigned int *gpiod_pdor = (unsigned int *)(GPIOD + PDOR);
    unsigned int *gpiod_pddr = (unsigned int *)(GPIOD + PDDR);

    f_ConfigureGPIO(pcc_portd, portd_pcr15);
    f_BitMaskRevision(gpiod_pddr, 15, SET_BIT); /*SET DIRECTION as Output*/
    f_BitMaskRevision(gpiod_pdor, 15, CLEAR_BIT);
}

void f_ConfigureGPIO(unsigned int *pcc_portx, unsigned int *port_pcrn)
{
    /*Clock Enable*/
    f_BitMaskRevision(pcc_portx, 30, SET_BIT);
    /*Set pin as GPIO. PIN 10-9-8 AS 0-0-1*/
    f_SetMultibit(port_pcrn, 8, 0x7, 0x1);
    /*DISABLE PULL-UP/PULL-DOWN*/
    f_BitMaskRevision(port_pcrn, 1, CLEAR_BIT); /*port_pcrn.PE - Pull Enable*/
    f_BitMaskRevision(port_pcrn, 0, CLEAR_BIT); /*port_pcrn.PS - Pull Disable*/
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
void f_Config_EN_DIS_LED(unsigned char color)
{
    unsigned int *pcc_portd = (unsigned int *)(PCC + PORTD);
    unsigned int *portd_pcr15 = (unsigned int *)(BASE_PORTD + 0x3C);
    unsigned int *portd_pcr16 = (unsigned int *)(BASE_PORTD + 0x40);
    unsigned int *portd_pcr0 = (unsigned int *)(BASE_PORTD + 0x00);
    unsigned int *gpiod_pdor = (unsigned int *)(GPIOD + PDOR);
    unsigned int *gpiod_pddr = (unsigned int *)(GPIOD + PDDR);
    unsigned int *pcc_portc = (unsigned int *)(PCC + PORTC);
    unsigned int *portc_pcr13 = (unsigned int *)(BASE_PORTC + 0X34);
    unsigned int *gpioc_pddr = (unsigned int *)(GPIOC + PDDR);
    /*unsigned int* gpioc_pdir = (unsigned int*) (GPIOC + PDIR);*/

    /*Config GPIO Output*/
    switch (color)
    {
    case RED_LED:
        f_ConfigureGPIO(pcc_portd, portd_pcr15);
        break;
    case GREEN_LED:
        f_ConfigureGPIO(pcc_portd, portd_pcr16);
        break;
    case BLUE_LED:
        f_ConfigureGPIO(pcc_portd, portd_pcr0);
        break;
    default:
        break;
    }

    f_BitMaskRevision(gpiod_pdor, color, SET_BIT); /*use to turn off led at the first time set up*/
    f_BitMaskRevision(gpiod_pddr, color, SET_BIT); /*SET DIRECTION as Output*/

    /*Config GPIO input*/
    f_ConfigureGPIO(pcc_portc, portc_pcr13);
    /*Set Input*/
    f_BitMaskRevision(gpioc_pddr, 13, CLEAR_BIT); /*SET PORT D PIN 13 as Input*/
}

void EN_DIS_LED(unsigned char color)
{
    unsigned int *gpiod_ptor = (unsigned int *)(GPIOD + PTOR);
    unsigned int *gpioc_pdir = (unsigned int *)(GPIOC + PDIR);
    if (ReadBit(gpioc_pdir, 13) == 1) /*Read status of SW3*/
        f_BitMaskRevision(gpiod_ptor, color, SET_BIT);
}

/*Read Bit to return value of bit is 0 or 1*/
unsigned char ReadBit(unsigned int *reg, unsigned char position)
{
    unsigned int temp;
    temp = *reg & (1 << position);
    if (temp != 0)
        return 1;
    else
        return 0;
}

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

void f_ConfigInterrupt(unsigned int *port_pcrn, unsigned char mode)
{
    /*Configure interrupt of peripheral on rising edge*/
    f_SetMultibit(port_pcrn, 16, 0x0F, mode); /*Set IRQC (interrupt type)*/
}

void f_ConfigNVIC(unsigned char id)
{
    unsigned char n = id / 32;
    unsigned char bitofisern = id % 32;
    unsigned int *isern = (unsigned int *)(NVIC_ISER + n * 4);
    f_BitMaskRevision(isern, bitofisern, SET_BIT);
}

unsigned char SwitchStatus(void)
{
    unsigned int *gpioc_pdir = (unsigned int *)(GPIOC + PDIR);
    if (ReadBit(gpioc_pdir, 12) == 1) /*Read status of SW2*/
        return 1;
    if (ReadBit(gpioc_pdir, 13) == 1)
        return 0;
    return 0;
}

void Active_LED(unsigned char color, unsigned char mode)
{
    unsigned int *gpiod_pdor = (unsigned int *)(GPIOD + PDOR);
    if (mode == 1)
    {
        f_BitMaskRevision(gpiod_pdor, color, CLEAR_BIT);
        f_delay(2000000);
        f_BitMaskRevision(gpiod_pdor, color, SET_BIT);
    }
    else if (mode == 0)
        f_BitMaskRevision(gpiod_pdor, color, SET_BIT);
}

unsigned char f_FindPinISF(unsigned int *portx_isf)
{
    unsigned char position = 0;
    while (ReadBit(portx_isf, position) == 0)
    {
        position++;
    }
    return position;
}

void Blink_RGBLED(void)
{
    Active_LED(RED_LED, HIGH);
    Active_LED(GREEN_LED, HIGH);
    Active_LED(BLUE_LED, HIGH);
}
void TurnOFF_RGBLed(void)
{
    Active_LED(RED_LED, LOW);
    Active_LED(GREEN_LED, LOW);
    Active_LED(BLUE_LED, LOW);
}

void PORTC_IRQHandler(void)
{ 
    unsigned int *portc_isf = (unsigned int *)(BASE_PORTC + 0xA0);
    unsigned char pin = f_FindPinISF(portc_isf);
    if (pin == 12)
    {
        g_mode = 1;
        f_BitMaskRevision(portc_isf, 12, SET_BIT);
    }
    else if (pin == 13)
    {
        g_mode = 2;
        f_BitMaskRevision(portc_isf, 13, SET_BIT);
    }
}

void f_delay(unsigned int second)
{
    unsigned int count = 0;
    second*=1000000;
    do
    {
        count++;
    } while (count < second);
}
