/*
 * lvr_evth.h
 *
 *  Created on: 21 окт. 2018 г.
 *      Author: lvr_laptop
 */

#ifndef PERIPH_DEV_CPROJ_LVR_BLE_LVR_EVTH_LVR_EVTH_H_
#define PERIPH_DEV_CPROJ_LVR_BLE_LVR_EVTH_LVR_EVTH_H_

#include "../global_defs.h"
#include "../debug.h"

typedef void (* cb)(bool);

void ble_evt_dispatch(ble_evt_t * p_ble_evt);
void EVTH_RegCallb(cb fPtr);

#endif /* PERIPH_DEV_CPROJ_LVR_BLE_LVR_EVTH_LVR_EVTH_H_ */
