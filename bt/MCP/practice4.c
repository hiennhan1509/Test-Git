#include "LED.h"
#include "BitManipulation.h"
#include "S32K144_Address.h"

void f_Config_LED(unsigned char color)
{
    unsigned int *pcc_portd = (unsigned int *)(PCC + PORTD);
    unsigned int *portd_pcr15 = (unsigned int *)(BASE_PORTD + 0x3C);
    unsigned int *portd_pcr16 = (unsigned int *)(BASE_PORTD + 0x40);
    unsigned int *portd_pcr0 = (unsigned int *)(BASE_PORTD + 0x00);
    unsigned int *gpiod_pdor = (unsigned int *)(GPIOD + PDOR);
    unsigned int *gpiod_pddr = (unsigned int *)(GPIOD + PDDR);
    /*unsigned int* gpioc_pdir = (unsigned int*) (GPIOC + PDIR);*/

    /*Enable Clocl, Set GPIO Output*/
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
}

/*ON-OFF LED*/
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

/* Change color of LED*/
void Blink_RGBLED(void)
{
    Active_LED(RED_LED, HIGH);
    Active_LED(GREEN_LED, HIGH);
    Active_LED(BLUE_LED, HIGH);
}

/*Turn OFF LED*/
void TurnOFF_RGBLed(void)
{
    Active_LED(RED_LED, LOW);
    Active_LED(GREEN_LED, LOW);
    Active_LED(BLUE_LED, LOW);
}

/*Configure Switch*/
void f_Config_SW(unsigned char sw)
{
    unsigned int *pcc_portc = (unsigned int *)(PCC + PORTC);
    unsigned int *portc_pcr12 = (unsigned int *)(BASE_PORTC + 0X30);
    unsigned int *portc_pcr13 = (unsigned int *)(BASE_PORTC + 0X34);
    unsigned int *gpioc_pddr = (unsigned int *)(GPIOC + PDDR);

    if (sw == 2)
    {
        f_ConfigureGPIO(pcc_portc, portc_pcr12);
        /*Set Input*/
        f_BitMaskRevision(gpioc_pddr, 12, CLEAR_BIT); /*SET PORT D PIN 13 as Input*/
    }
    else if (sw == 3)
    {
        f_ConfigureGPIO(pcc_portc, portc_pcr13);
        /*Set Input*/
        f_BitMaskRevision(gpioc_pddr, 13, CLEAR_BIT); /*SET PORT D PIN 13 as Input*/
    }
}
