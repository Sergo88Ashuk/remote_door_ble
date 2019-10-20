/*
 * lvr_gpio.h
 *
 *  Created on: 12 сент. 2018 г.
 *      Author: lvr_laptop
 */

#ifndef BARE_DRIVERS_CPROJ_LVR_GPIO_H_
#define BARE_DRIVERS_CPROJ_LVR_GPIO_H_

#include "global_defs.h"

#define GPIOLVR_BA				(0x50000000UL)

#define GPIOLVR_OUT_OFFSET		(0x504)
#define GPIOLVR_OUT				(*((volatile uint32_t*) (GPIOLVR_BA + GPIOLVR_OUT_OFFSET)))
#define GPIOLVR_OUTSET_OFFSET	(0x508)
#define GPIOLVR_OUTSET			(*((volatile uint32_t*) (GPIOLVR_BA + GPIOLVR_OUTSET_OFFSET)))
#define GPIOLVR_OUTCLR_OFFSET	(0x50C)
#define GPIOLVR_OUTCLR			(*((volatile uint32_t*) (GPIOLVR_BA + GPIOLVR_OUTCLR_OFFSET)))
#define GPIOLVR_IN_OFFSET		(0x510)
#define GPIOLVR_IN				(*((volatile uint32_t*) (GPIOLVR_BA + GPIOLVR_IN_OFFSET)))
#define GPIOLVR_DIR_OFFSET		(0x514)
#define GPIOLVR_DIR				(*((volatile uint32_t*) (GPIOLVR_BA + GPIOLVR_DIR_OFFSET)))
#define GPIOLVR_DIRSET_OFFSET	(0x518)
#define GPIOLVR_DIRSET			(*((volatile uint32_t*) (GPIOLVR_BA + GPIOLVR_DIRSET_OFFSET)))
#define GPIOLVR_DIRCLR_OFFSET	(0x51C)
#define GPIOLVR_DIRCLR			(*((volatile uint32_t*) (GPIOLVR_BA + GPIOLVR_DIRCLR_OFFSET)))
#define GPIOLVR_CNF_OFFSET		(0x700)
#define GPIOLVR_CNF				(((volatile uint32_t*) (GPIOLVR_BA + GPIOLVR_CNF_OFFSET)))

//#define GPIO_OUT

#define GPIOLVR_CNF_DIR_OFFSET		(0)
#define GPIOLVR_CNF_INBUF_OFFSET	(1)
#define GPIOLVR_CNF_PULLUP_OFFSET	(2)
#define GPIOLVR_CNF_DRIVE_OFFSET	(8)
#define GPIOLVR_CNF_SENSE_OFFSET	(16)
#define GPIOLVR_DIR_IN_Msk			(0)
#define GPIOLVR_DIR_OUT_Msk			(1)
#define GPIOLVR_INBUF_CONN_Msk		(0)
#define GPIOLVR_INBUF_DISC_Msk		(1)
#define GPIOLVR_PULLUP_DISABLE_Msk	(0)
#define GPIOLVR_PULLUP_DOWN_Msk		(1)
#define GPIOLVR_PULLUP_UP_Msk		(3)
#define GPIOLVR_DRIVE_S0S1_Msk		(0)
#define GPIOLVR_DRIVE_H0S1_Msk		(1)
#define GPIOLVR_DRIVE_S0H1_Msk		(2)
#define GPIOLVR_DRIVE_H0H1_Msk		(3)
#define GPIOLVR_DRIVE_D0S1_Msk		(4)
#define GPIOLVR_DRIVE_D0H1_Msk		(5)
#define GPIOLVR_DRIVE_S0D1_Msk		(6)
#define GPIOLVR_DRIVE_H0D1_Msk		(7)
#define GPIOLVR_SENSE_DISABLE_Msk	(0)
#define GPIOLVR_SENSE_HIGH_Msk		(2)
#define GPIOLVR_SENSE_LOW_Msk		(3)

#define GPIO_0	(0)
#define GPIO_1	(1)
#define GPIO_2	(2)
#define GPIO_3	(3)
#define GPIO_4	(4)
#define GPIO_5	(5)
#define GPIO_6	(6)
#define GPIO_7	(7)
#define GPIO_8	(8)
#define GPIO_9	(9)
#define GPIO_10	(10)
#define GPIO_11	(11)
#define GPIO_12	(12)

void GPIOLVR_Init(uint8_t pinNum, bool outPut);
void GPIOLVR_On(uint8_t pinNum);
void GPIOLVR_Off(uint8_t pinNum);
void GPIOLVR_Toggle(uint8_t pinNum);
bool GPIOLVR_Get(uint8_t pinNum);

#endif /* BARE_DRIVERS_CPROJ_LVR_GPIO_H_ */
