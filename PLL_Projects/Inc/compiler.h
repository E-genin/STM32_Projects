/*
 * compiler.h
 *
 *  Created on: Mar 15, 2024
 *      Author: zakar
 */

#ifndef COMPILER_H_
#define COMPILER_H_


#include <stdint.h>

#define REG_ACCESS(x)   (*((volatile uint32_t *)(x)))

#endif /* COMPILER_H_ */
