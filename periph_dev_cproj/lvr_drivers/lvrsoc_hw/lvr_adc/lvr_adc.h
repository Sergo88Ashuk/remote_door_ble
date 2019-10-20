/*
 * lvr_adc.h
 *
 *  Created on: 24 но€б. 2018 г.
 *      Author: lvr_laptop
 */

#ifndef PERIPH_DEV_CPROJ_LVR_DRIVERS_LVRSOC_HW_LVR_ADC_LVR_ADC_H_
#define PERIPH_DEV_CPROJ_LVR_DRIVERS_LVRSOC_HW_LVR_ADC_LVR_ADC_H_

#include "global_defs.h"

#define HIGH	(1)
#define LOW		(0)

#define ADCLVR_BA				(0x40007000)

#define ADCLVR_START_OFFSET		(0x00)
#define ADCLVR_STOP_OFFSET		(0x04)
#define ADCLVR_END_OFFSET		(0x100)
#define ADCLVR_INTEN_OFFSET		(0x300)
#define ADCLVR_INTENSET_OFFSET	(0x304)
#define ADCLVR_INTENCLR_OFFSET	(0x308)
#define ADCLVR_BUSY_OFFSET		(0x400)
#define ADCLVR_ENABLE_OFFSET	(0x500)
#define ADCLVR_CONFIG_OFFSET	(0x504)
#define ADCLVR_RESULT_OFFSET	(0x508)

#define ADCLVR_START			(*((volatile uint32_t*)(ADCLVR_BA + ADCLVR_START_OFFSET)))
#define ADCLVR_STOP				(*((volatile uint32_t*)(ADCLVR_BA + ADCLVR_STOP_OFFSET)))
#define ADCLVR_END				(*((volatile uint32_t*)(ADCLVR_BA + ADCLVR_END_OFFSET)))
#define ADCLVR_INTEN			(*((volatile uint32_t*)(ADCLVR_BA + ADCLVR_INTEN_OFFSET)))
#define ADCLVR_INTENSET			(*((volatile uint32_t*)(ADCLVR_BA + ADCLVR_INTENSET_OFFSET)))
#define ADCLVR_INTENCLR			(*((volatile uint32_t*)(ADCLVR_BA + ADCLVR_INTENCLR_OFFSET)))
#define ADCLVR_BUSY				(*((volatile uint32_t*)(ADCLVR_BA + ADCLVR_BUSY_OFFSET)))
#define ADCLVR_ENABLE			(*((volatile uint32_t*)(ADCLVR_BA + ADCLVR_ENABLE_OFFSET)))
#define ADCLVR_CONFIG			(*((volatile uint32_t*)(ADCLVR_BA + ADCLVR_CONFIG_OFFSET)))
#define ADCLVR_RESULT			(*((volatile uint32_t*)(ADCLVR_BA + ADCLVR_RESULT_OFFSET)))

#define ADCLVR_RES_OFFSET		(0)
#define ADCLVR_RES_MASK			(0x03)
#define RES_8B					(0)
#define RES_9B					(1)
#define RES_10B					(2)

#define ADCLVR_INPSEL_OFFSET	(2)
#define ADCLVR_INPSEL_MASK		(0x07)
#define ANIN_0_PRSCL			(0)
#define ANIN_2_3_PRSCL			(1)
#define ANIN_1_3_PRSCL			(2)
#define VDD_IN_2_3_PRSCL			(5)
#define VDD_IN_1_3_PRSCL			(6)

#define ADCLVR_REFSEL_OFFSET	(5)
#define ADCLVR_REFSEL_MASK		(0x03)
#define INTERN_1_2_V			(0)
#define EXTERN					(1)
#define VDD_REF_1_2_PRSCL			(2)
#define VDD_REF_1_3_PRSCL			(3)

#define ADCLVR_PINSEL_OFFSET	(8)
#define ADCLVR_PINSEL_MASK		(0xFF)
#define ANIN0					(1)
#define ANIN1					(2)
#define ANIN2					(4)
#define ANIN3					(8)
#define ANIN4					(16)
#define ANIN5					(32)
#define ANIN6					(64)
#define ANIN7					(128)

#define ADCLVR_EXTREF_OFFSET	(16)



void ADCLVR_Init(void);
void ADCLVR_Start(void);
uint32_t ADCLVR_Get(void);


#endif /* PERIPH_DEV_CPROJ_LVR_DRIVERS_LVRSOC_HW_LVR_ADC_LVR_ADC_H_ */
