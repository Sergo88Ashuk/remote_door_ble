/*
 * lvr_tim.h
 *
 *  Created on: 23 но€б. 2018 г.
 *      Author: lvr_laptop
 */

#ifndef PERIPH_DEV_CPROJ_LVR_DRIVERS_LVRSOC_HW_LVR_TIM_LVR_TIM_H_
#define PERIPH_DEV_CPROJ_LVR_DRIVERS_LVRSOC_HW_LVR_TIM_LVR_TIM_H_

#include "global_defs.h"

#define HIGH	(1)
#define LOW		(0)

#define TIM1LVR_BA		(0x40009000)

#define TIM1LVR_START_OFFSET	(0x00)
#define TIM1LVR_STOP_OFFSET		(0x04)
#define TIM1LVR_COUNT_OFFSET	(0x08)
#define TIM1LVR_CLEAR_OFFSET	(0x0C)
#define TIM1LVR_SHUTDOWN_OFFSET	(0x10)
#define TIM1LVR_CAPTURE_OFFSET	(0x40)
#define TIM1LVR_COMPARE_OFFSET	(0x140)
#define TIM1LVR_SHORTS_OFFSET	(0x200)
#define TIM1LVR_INTENSET_OFFSET	(0x304)
#define TIM1LVR_INTENCLR_OFFSET	(0x308)
#define TIM1LVR_MODE_OFFSET		(0x504)
#define TIM1LVR_BITMODE_OFFSET	(0x508)
#define TIM1LVR_PRSCL_OFFSET	(0x510)
#define TIM1LVR_CAPCOM_OFFSET	(0x540)

#define TIM1LVR_START			(*((volatile uint32_t*)(TIM1LVR_BA + TIM1LVR_START_OFFSET)))
#define TIM1LVR_STOP			(*((volatile uint32_t*)(TIM1LVR_BA + TIM1LVR_STOP_OFFSET)))
#define TIM1LVR_COUNT			(*((volatile uint32_t*)(TIM1LVR_BA + TIM1LVR_COUNT_OFFSET)))
#define TIM1LVR_CLEAR			(*((volatile uint32_t*)(TIM1LVR_BA + TIM1LVR_CLEAR_OFFSET)))
#define TIM1LVR_SHUTDOWN		(*((volatile uint32_t*)(TIM1LVR_BA + TIM1LVR_SHUTDOWN_OFFSET)))
#define TIM1LVR_CAPTURE			(*((volatile uint32_t*)(TIM1LVR_BA + TIM1LVR_CAPTURE_OFFSET)))
#define TIM1LVR_COMPARE			((volatile uint32_t*)(TIM1LVR_BA + TIM1LVR_COMPARE_OFFSET))
#define TIM1LVR_SHORTS			(*((volatile uint32_t*)(TIM1LVR_BA + TIM1LVR_SHORTS_OFFSET)))
#define TIM1LVR_INTENSET		(*((volatile uint32_t*)(TIM1LVR_BA + TIM1LVR_INTENSET_OFFSET)))
#define TIM1LVR_INTENCLR		(*((volatile uint32_t*)(TIM1LVR_BA + TIM1LVR_INTENCLR_OFFSET)))
#define TIM1LVR_MODE			(*((volatile uint32_t*)(TIM1LVR_BA + TIM1LVR_MODE_OFFSET)))
#define TIM1LVR_BITMODE			(*((volatile uint32_t*)(TIM1LVR_BA + TIM1LVR_BITMODE_OFFSET)))
#define TIM1LVR_PRSCL			(*((volatile uint32_t*)(TIM1LVR_BA + TIM1LVR_PRSCL_OFFSET)))
#define TIM1LVR_CAPCOM			(*((volatile uint32_t*)(TIM1LVR_BA + TIM1LVR_CAPCOM_OFFSET)))

#define CMP0_OFFSET		(16)
#define CMP1_OFFSET		(17)
#define CMP2_OFFSET		(18)
#define CMP3_OFFSET		(19)

void TIM1LVR_Init(void);
void TIM1LVR_Start(void);
void TIM1LVR_Stop(void);

#endif /* PERIPH_DEV_CPROJ_LVR_DRIVERS_LVRSOC_HW_LVR_TIM_LVR_TIM_H_ */
