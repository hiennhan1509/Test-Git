/****************************************************************/
/**
 *  file        main.c
 *  containts   Run application code
 */
/****************************************************************/

/****************************************************************/
/*  Includes section                                            */
/****************************************************************/
//#include 
#include <stdio.h>

/****************************************************************/
/*  Types And Constants                                         */
#define SET_BIT 1
#define CLEAR_BIT 0

/****************************************************************/

/****************************************************************/
/*  Internal function prototype                                 */
/****************************************************************/
/*use to SET BIT or CLEAR BIT at n position*/
void f_BitMaskRevision(unsigned int* iAddress, unsigned char iPosition, unsigned char iAction);

/*Delay Function*/
void f_delay(unsigned short nSecond);
/*Configure Function*/
void f_ConfigureOutput(unsigned int* PCC_PORTX, unsigned int* PORT_PCRn);
/*TOGGLE BIT Function*/
void f_ToggleBit(unsigned int* GPIOX_BASE, unsigned int* GPIOX_PDDR, unsigned char nPos);
/*TOGGLE BLINK LED Function*/
void f_BlinkRedLed(void);


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
	unsigned int Number = 5;
	unsigned int *Address = &Number;
	unsigned char nPosition = 2;
	f_BitMaskRevision(Address, nPosition, SET_BIT);
    unsigned int *GPIOD_BASE = (unsigned int*) 0X40065000;
	
    unsigned int *GPIOD_BASE2 = (unsigned int*) (0X40065000 + 0X12C);
    // unsigned int *GPIOD_BASE3 = (unsigned int*) (GPIOD_BASE + a);
	// unsigned int* GPIOD_PDDR = GPIOD_BASE + 0X14;
    printf("\n");
    printf("%X",GPIOD_BASE2);
	printf("\n");
    // printf("%X",GPIOD_BASE3);

	return 0;
}

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

void f_BitMaskRevision(unsigned int* iAddress, unsigned char iPosition, unsigned char iAction)
{
	if(iAction == 1)
	{
		*iAddress |= 1<<iPosition; /*Set bit at n Position = 1*/
	}else
	{
		*iAddress &= ~(1<<iPosition); /*Set bit at n Position = 0*/
	}
}

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

// void f_BlinkRedLed(void)
// {
// 	unsigned int* PCC_PORTD = 0x40065000 + 0x130;
// 	unsigned int* PORT_PCR15 = 0x404C000 + 0x3C;
// 	unsigned int* GPIOD_BASE = 0x400FF0C0;
// 	unsigned int* GPIOD_PDDR = GPIOD_BASE + 0x14;
// 	unsigned char nPosition = 15;
// 	f_ConfigureOutput(PCC_PORTD, PORT_PCR15);
// 	f_ToggleBit(GPIOD_BASE,GPIOD_PDDR, nPosition);
	
// }

void f_ConfigureOutput(unsigned int* PCC_PORTX, unsigned int* PORT_PCRn)
{
	/*Clock Enable*/
	f_BitMaskRevision(PCC_PORTX,30,SET_BIT);
	/*Set pin as GPIO. PIN 10-9-8 AS 0-0-1*/
	f_BitMaskRevision(PORT_PCRn,8,SET_BIT);
	f_BitMaskRevision(PORT_PCRn,9,CLEAR_BIT);
	f_BitMaskRevision(PORT_PCRn,10,CLEAR_BIT);
	/*DISABLE PULL-UP/PULL-DOWN*/
	f_BitMaskRevision(PORT_PCRn,1,CLEAR_BIT); /*PORT_PCRn.PE - Pull Enable*/
	f_BitMaskRevision(PORT_PCRn,0,CLEAR_BIT); /*PORT_PCRn.PS - Pull Disable*/
}

void f_ToggleBit(unsigned int* GPIOX_BASE, unsigned int* GPIOX_PDDR, unsigned char nPos)
{	
	/*Set Output*/
	f_BitMaskRevision(GPIOX_PDDR,15,SET_BIT); /*SET PIN 15 as Output*/
	while(1)
	{
		f_BitMaskRevision(GPIOX_BASE + 0x0C,nPos,SET_BIT);
		f_delay(1000);
	}
}

void f_delay(unsigned short nSecond)
{
	unsigned short count = 0;
	do{
		count++;
	}while(count<nSecond);
}
