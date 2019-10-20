/*
 * lvr_evth.c
 *
 *  Created on: 21 окт. 2018 г.
 *      Author: lvr_laptop
 */

#include "lvr_evth.h"

cb ConStateUpdate;

static void _AppEventHandler(ble_evt_t * p_ble_evt);

void EVTH_RegCallb(cb fPtr)
{
	ConStateUpdate = fPtr;
}

void ble_evt_dispatch(ble_evt_t * p_ble_evt)
{
	DBG("\r\nevt_code [0x%02X]", p_ble_evt->header.evt_id);
    ble_conn_state_on_ble_evt(p_ble_evt);
    ble_conn_params_on_ble_evt(p_ble_evt);

    _AppEventHandler(p_ble_evt);
}

static void _AppEventHandler(ble_evt_t * p_ble_evt)
{
	ble_gatts_evt_write_t* dataIn;
	if (p_ble_evt->header.evt_id == BLE_GATTS_EVT_WRITE)
	{
		dataIn = &p_ble_evt->evt.gatts_evt.params.write;
		DBG("\r\nhandle: [0x%02X]",(unsigned int) dataIn->handle);
		DBG("\r\nuuid:   [0x%02X]",(unsigned int) dataIn->uuid.uuid);
		DBG("\r\ndata0:  [0x%02X]",(unsigned int) dataIn->data[0]);
		DBG("\r\ndata0:  [0x%02X]",(unsigned int) dataIn->data[1]);
	}

	if (p_ble_evt->header.evt_id == BLE_GAP_EVT_CONNECTED)
	{
		ConStateUpdate(true);
	}

	if (p_ble_evt->header.evt_id == BLE_GAP_EVT_DISCONNECTED)
	{
		ConStateUpdate(false);
	}
}
