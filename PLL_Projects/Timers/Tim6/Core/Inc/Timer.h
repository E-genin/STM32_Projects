/*
 * Timer.h
 *
 *  Created on: Mar 20, 2024
 *      Author: zakar
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include <stdint.h>

void Write_Values_In_Register(uint32_t Address, uint32_t Start_Position, uint32_t Length, uint32_t Value);

void McuInit(void);

void Init_Timer6(void);

void Start_Timer6(void);

uint8_t Get_Timer6_Status(void);

void LED1_Configure(void);

void LED1_Toggle(void);

void delay_1ms(void);

#define 	TIMER_6_REGISTER_BASE_ADDRESSE 	0x40001000
#define 	RCC_REGISTER_BASE_ADDRESSE 		0x40023800
#define     RCC_REGISTER_BASE_ADDRESS   0x40023800U
#define     GPIO_BASE_ADDRESS           0x40020000U

#define     MY_RCC_CR_OFFSET               0x00000000U
#define     MY_RCC_PLLCFGR_OFFSET          0x00000004U
#define     MY_RCC_CFGR_OFFSET             0x00000008U
#define     MY_RCC_AHB1ENR_OFFSET          0x00000030U
#define     MY_GPIOx_MODER_OFFSET          0x00000000U

#define RCC_APB1ENR_OFFSET	0x00000040
#define TIMx_PSC_OFFSET		0x00000028
#define TIMx_CR1_OFFSET		0x00000000
#define TIMx_ARR_OFFSET		0x0000002C
#define TIMx_SR_OFFSET		0x00000010

#endif /* INC_TIMER_H_ */
