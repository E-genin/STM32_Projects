/*
 * Init.h
 *
 *  Created on: Mar 15, 2024
 *      Author: zakar
 */

#ifndef INIT_H_
#define INIT_H_


#include <stdint.h>

#define     RCC_REGISTER_BASE_ADDRESS   0x40023800U
#define     GPIO_BASE_ADDRESS           0x40020000U

#define     MY_RCC_CR_OFFSET               0x00000000U
#define     MY_RCC_PLLCFGR_OFFSET          0x00000004U
#define     MY_RCC_CFGR_OFFSET             0x00000008U
#define     MY_RCC_AHB1ENR_OFFSET          0x00000030U
#define     MY_GPIOx_MODER_OFFSET          0x00000000U

void McuInit(void);
void Mco1Init(void);
void Write_Values_In_Register(uint32_t Address, uint32_t Start_Position, uint32_t Length, uint32_t Value);


#endif /* INIT_H_ */
