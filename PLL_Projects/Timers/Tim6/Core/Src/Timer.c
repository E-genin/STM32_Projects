/*
 * Timer.c
 *
 *  Created on: Mar 20, 2024
 *      Author: zakar
 */


#include "Timer.h"
#include "stm32f4xx.h"



#define REG_ACCESS(x)   (*((volatile uint32_t *)(x)))

void Write_Values_In_Register(uint32_t Address, uint32_t Start_Position, uint32_t Length, uint32_t Value)
{
    uint32_t Mask = ~(((1U << Length)-1)<< Start_Position);

    REG_ACCESS(Address) &= (Mask);
    REG_ACCESS(Address) |= (Value << Start_Position);

}

void McuInit()
{
    // Enabling HSE
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_CR_OFFSET),16,1,1);

    // Waiting for the HSE to be ready
    while(((REG_ACCESS((RCC_REGISTER_BASE_ADDRESS+MY_RCC_CR_OFFSET))) & (1U<<17))==0);

    // Set M Divider for PLL = 8
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_PLLCFGR_OFFSET),0,6,8);

    // Set N Multiplier for PLL = 192
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_PLLCFGR_OFFSET),6,9,192);


    // Set P Divider for PLL = 6
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_PLLCFGR_OFFSET),16,2,2);

    // Set Q Divider for PLL = 4
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_PLLCFGR_OFFSET),24,4,4);

    // Set HSE as PLL Source
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_PLLCFGR_OFFSET),22,1,1);

    // Set APB1 Prescaler = 4
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_CFGR_OFFSET),10,3,5);

    // Set APB2 Prescaler = 2
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_CFGR_OFFSET),13,3,4);

    // Enable PLL
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_CR_OFFSET),24,1,1);

    // Waiting for the PLL to be ready
    while(((REG_ACCESS((RCC_REGISTER_BASE_ADDRESS+MY_RCC_CR_OFFSET))) & (1U<<25))==0);

    // SWitch to PLL
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_CFGR_OFFSET),0,2,2);



    return ; // for debugging
}

void Init_Timer6()
{
	// Enabling Clocking link to Timer 6
	Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESSE+RCC_APB1ENR_OFFSET), 4, 1, 1);

	// Configuring Timer 6 Prescaler
	// APB1 Clock = 8 Mhz
	// Prescaler = 2 => Timer 6 Clock = 4 Mhz => 1 Tick = 0.250 us
	// The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1) => PSC = 1
	Write_Values_In_Register((TIMER_6_REGISTER_BASE_ADDRESSE+TIMx_PSC_OFFSET), 0, 16, 1);

}

void Start_Timer6()
{
	// Enabling Timer 6
	Write_Values_In_Register((TIMER_6_REGISTER_BASE_ADDRESSE+TIMx_CR1_OFFSET), 0, 1, 1);
}

uint8_t Get_Timer6_Status()
{
	uint16_t Timer6_Status = REG_ACCESS((TIMER_6_REGISTER_BASE_ADDRESSE+TIMx_SR_OFFSET)) ;

	uint8_t UIF_Flag = (Timer6_Status & (1<<0));

	return UIF_Flag;
}

void delay_1ms()
{
	// Configuring the Timer value = 4000 = 1ms/0.25us (1 tick = 0.25us)
	Write_Values_In_Register((TIMER_6_REGISTER_BASE_ADDRESSE+TIMx_ARR_OFFSET), 0, 16, 4000-1);

	Start_Timer6();

	// Wait for the UIF Flag to raise (Timer counter has reached the ARR value)
	while	(Get_Timer6_Status()==0x00);

	// Clearing the Update Interrupt Flag UIF
	Write_Values_In_Register((TIMER_6_REGISTER_BASE_ADDRESSE+TIMx_SR_OFFSET), 0, 1, 0);
}

void LED1_Configure()
{
	// Enabling the Clocking AHB1 (Tim6 is mounted on AHB1)
	SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);

	// Configuring the Pin PB0 (LD1) to behave as Output
	Write_Values_In_Register(GPIOB_BASE+0x00000000, 0, 2, 1) ;

	// Choosing Push-Pull Configuration
	Write_Values_In_Register(GPIOB_BASE+0x00000004, 0, 1, 0) ;
}

void LED1_Toggle()
{
	uint8_t Led_status = (REG_ACCESS(GPIOB_BASE+0x00000014) & (1<<0));

	if(Led_status) Write_Values_In_Register(GPIOB_BASE+0x00000014, 0, 1, 0);
	else Write_Values_In_Register(GPIOB_BASE+0x00000014, 0, 1, 1);
}
