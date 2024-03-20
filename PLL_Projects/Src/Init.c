/*
 * Init.c
 *
 *  Created on: Mar 15, 2024
 *      Author: zakar
 */

#include "Init.h"
#include "compiler.h"


void Write_Values_In_Register(uint32_t Address, uint32_t Start_Position, uint32_t Length, uint32_t Value)
{
    uint32_t Mask = ~(((1U << Length)-1)<< Start_Position);

    REG_ACCESS(Address) &= (Mask);
    REG_ACCESS(Address) |= (Value << Start_Position);

}

void McuInit()
{

	// HSE = 8 MHz
	// PLL  = HSE / M * N / P
	// PLL' = HSE / M * N / Q
	// M = 8, N = 192, P = 8, Q = 4

    // Enabling HSE
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_CR_OFFSET),16,1,1);

    // Waiting for the HSE to be ready
    while(((REG_ACCESS((RCC_REGISTER_BASE_ADDRESS+MY_RCC_CR_OFFSET))) & (1U<<17))==0);

    // Set M Divider for PLL = 8
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_PLLCFGR_OFFSET),0,6,8);

    // Set N Multiplier for PLL = 192
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_PLLCFGR_OFFSET),6,9,192);


    // Set P Divider for PLL = 8
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_PLLCFGR_OFFSET),16,2,3);

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

void Mco1Init()
{
    // Configuring MCO1 to take PLL as a source
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_CFGR_OFFSET),21,2,3);

    // Configuring Prescaler for MCO1 = 5
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_CFGR_OFFSET),24,3,7);

    // Enabling RCC for GPIOA
    Write_Values_In_Register((RCC_REGISTER_BASE_ADDRESS+MY_RCC_AHB1ENR_OFFSET),0,1,1);

    // Configuring PA8 for Alternate Function
    Write_Values_In_Register((GPIO_BASE_ADDRESS+MY_GPIOx_MODER_OFFSET),16,2,2);

    return ; // for debugging
}
