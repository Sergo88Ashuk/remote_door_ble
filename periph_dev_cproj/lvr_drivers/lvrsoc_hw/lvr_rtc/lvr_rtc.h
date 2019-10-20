/*
 * lvr_rtc.h
 *
 *  Created on: 20 но€б. 2018 г.
 *      Author: lvr_laptop
 */

#ifndef PERIPH_DEV_CPROJ_LVR_DRIVERS_LVRSOC_HW_LVR_RTC_LVR_RTC_H_
#define PERIPH_DEV_CPROJ_LVR_DRIVERS_LVRSOC_HW_LVR_RTC_LVR_RTC_H_

#include "global_defs.h"

#define RTC1_BA		(0x40011000)

#define RTC1LVR_START_OFFSET		(0x00)
#define RTC1LVR_STOP_OFFSET			(0x04)
#define RTC1LVR_CLEAR_OFFSET		(0x08)
#define RTC1LVR_TICK_EVT_OFFSET		(0x100)
#define RTC1LVR_OVRFLW_EVT_OFFSET	(0x104)
#define RTC1LVR_INTEN_OFFSET		(0x300)
#define RTC1LVR_INTENSET_OFFSET		(0x304)
#define RTC1LVR_INTENCLR_OFFSET		(0x308)
#define RTC1LVR_EVTEN_OFFSET		(0x340)
#define RTC1LVR_EVTENSET_OFFSET		(0x344)
#define RTC1LVR_EVTENCLR_OFFSET		(0x348)
#define RTC1LVR_COUNTER_OFFSET		(0x504)
#define RTC1LVR_PSCKL_OFFSET		(0x508)

#define RTC1LVR_START			(*((volatile uint32_t*)(RTC1_BA + RTC1LVR_START_OFFSET)))
#define RTC1LVR_STOP			(*((volatile uint32_t*)(RTC1_BA + RTC1LVR_STOP_OFFSET)))
#define RTC1LVR_CLEAR			(*((volatile uint32_t*)(RTC1_BA + RTC1LVR_CLEAR_OFFSET)))
#define RTC1LVR_TICK_EVT		(*((volatile uint32_t*)(RTC1_BA + RTC1LVR_TICK_EVT_OFFSET)))
#define RTC1LVR_OVRFLW_EVT		(*((volatile uint32_t*)(RTC1_BA + RTC1LVR_OVRFLW_EVT_OFFSET)))
#define RTC1LVR_INTEN			(*((volatile uint32_t*)(RTC1_BA + RTC1LVR_INTEN_OFFSET)))
#define RTC1LVR_INTENSET		(*((volatile uint32_t*)(RTC1_BA + RTC1LVR_INTENSET_OFFSET)))
#define RTC1LVR_INTENCLR		(*((volatile uint32_t*)(RTC1_BA + RTC1LVR_INTENCLR_OFFSET)))
#define RTC1LVR_EVTEN			(*((volatile uint32_t*)(RTC1_BA + RTC1LVR_EVTEN_OFFSET)))
#define RTC1LVR_EVTENSET		(*((volatile uint32_t*)(RTC1_BA + RTC1LVR_EVTENSET_OFFSET)))
#define RTC1LVR_EVTENCLR		(*((volatile uint32_t*)(RTC1_BA + RTC1LVR_EVTENCLR_OFFSET)))
#define RTC1LVR_COUNTER			(*((volatile uint32_t*)(RTC1_BA + RTC1LVR_COUNTER_OFFSET)))
#define RTC1LVR_PSCKL			(*((volatile uint32_t*)(RTC1_BA + RTC1LVR_PSCKL_OFFSET)))

void RTC1LVR_Init(void);
void RTC1LVR_Start(void);
void RTC1LVR_Stop(void);

#endif /* PERIPH_DEV_CPROJ_LVR_DRIVERS_LVRSOC_HW_LVR_RTC_LVR_RTC_H_ */
