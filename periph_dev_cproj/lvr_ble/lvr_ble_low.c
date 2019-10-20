/*
 * lvr_ble.c
 *
 *  Created on: 13 окт. 2018 г.
 *      Author: lvr_laptop
 */

#include "lvr_ble_low.h"
#include "lvr_errh/lvr_errh.h"
#include "lvr_evth/lvr_evth.h"

extern uint32_t __data_start__;
volatile uint32_t ram_start = (uint32_t) &__data_start__;
uint32_t evtBuf[(sizeof(ble_evt_t) / 4) + 1];
static bool _EnableSoftDeviceInt(void);

void EnableAdvert(LVR_Advert_Mode* advMode)
{
	uint32_t errCode;
    if (advMode->state)
    {
    	errCode = sd_ble_gap_tx_power_set(advMode->txPower);
    	_APP_ERROR_CHECK(errCode);
    	DBG("\r\ntx [0x%02X]", (unsigned int) advMode->txPower);

    	errCode = sd_ble_gap_device_name_set(&advMode->secMode,
    										(uint8_t const*) advMode->devName,
											advMode->devNameLen);
    	_APP_ERROR_CHECK(errCode);

    	errCode = ble_advdata_set(&advMode->advData, NULL);
    	_APP_ERROR_CHECK(errCode);

    	errCode = sd_ble_gap_adv_start(&advMode->advParam);
    	_APP_ERROR_CHECK(errCode);
    }
    else
    {
    	errCode = sd_ble_gap_adv_stop();
    	if (errCode != NRF_ERROR_INVALID_STATE) // this err means adv already off (googled)
    		{_APP_ERROR_CHECK(errCode);}
    }
}

uint8_t SdGetAttr(LVR_Charac* charac)
{
	uint32_t errCode;
	volatile uint8_t retVal;
	ble_gatts_value_t getVal;
	getVal.len = 1;
	getVal.offset = 0;
	getVal.p_value = (uint8_t*) &retVal;

	errCode = sd_ble_gatts_value_get(BLE_CONN_HANDLE_INVALID,
									charac->char_handles.value_handle,
									&getVal);
	_APP_ERROR_CHECK(errCode);

	return retVal;
}

void SdSetAttr(LVR_Charac* charac, uint8_t* val)
{
	uint32_t errCode;
	ble_gatts_value_t setVal;
	setVal.len = 1;
	setVal.offset = 0;
	setVal.p_value = val;
	errCode = sd_ble_gatts_value_set(BLE_CONN_HANDLE_INVALID,
									charac->char_handles.value_handle,
									&setVal);
	_APP_ERROR_CHECK(errCode);
}

static bool _EnableSoftDeviceInt(void)
{
	uint32_t errCode;
	errCode = sd_nvic_EnableIRQ(SWI2_IRQn);
	_APP_ERROR_CHECK(errCode);
	return true;
}

bool EnableSoftDevice(LVR_Softdevice_Params* enableParams)
{
	uint32_t errCode;
	if(enableParams->sdState)
	{
		errCode = sd_softdevice_enable(&enableParams->clock,
										(nrf_fault_handler_t) *enableParams->softDevFaultHandler);
		_APP_ERROR_CHECK(errCode);
		_EnableSoftDeviceInt();
	}
	else
	{
		errCode = sd_softdevice_disable();
		_APP_ERROR_CHECK(errCode);
	}

	return true;
}

bool EnableBleStack(LVR_BleStack_Params* enableParams)
{
	uint32_t errCode;
	uint32_t app_ram_base;
	app_ram_base = ram_start;

//	DBG("\r\nram_addr: 0x%02X; params: 0x%02X", (unsigned int) &app_ram_base, (unsigned int) &enableParams->bleModule);

	errCode = sd_ble_enable(&enableParams->bleModule, &app_ram_base);
	_APP_ERROR_CHECK(errCode);
	return true;
}

bool AddUuid(LVR_Service_Uuid* servUuid)
{
	uint32_t errCode;
	errCode = sd_ble_uuid_vs_add(&servUuid->uuid128, &servUuid->uuid16.type);
	_APP_ERROR_CHECK(errCode);
	return true;
}

bool AddService(LVR_Service* service)
{
	uint32_t errCode;
	service->servUuid.uuid16.uuid = 0x1523;
	errCode = sd_ble_gatts_service_add(service->servType, &service->servUuid.uuid16, &service->handle);
	_APP_ERROR_CHECK(errCode);
	return true;
}

void AddCharac(LVR_Charac* charac, uint16_t handle)
{
	uint32_t errCode;
	errCode = sd_ble_gatts_characteristic_add(handle, &charac->char_md, &charac->attr_char_value, &charac->char_handles);
	_APP_ERROR_CHECK(errCode);
}

void SWI2_IRQHandler(void)
{
	DBG("\r\n..SWI2..");
	bool noEvt = false;
	for(;;)
	{
		uint32_t errCode;
		ble_evt_t* bleEvt = (ble_evt_t*) evtBuf;
		uint16_t bufLenDw = sizeof(evtBuf);

		errCode = sd_ble_evt_get((uint8_t*) bleEvt, &bufLenDw);

		if (errCode == NRF_ERROR_NOT_FOUND)
		{
			noEvt = true;
		}
		else if (errCode != NRF_SUCCESS)
		{
			AppError appErr =
			{
				.line    = __LINE__,
				.file    = __FILE__,
				.errC     = errCode,
			};
			AppErrorHandl(NRF_FAULT_ID_SDK_ERROR, 0, &appErr);
		}
		else
		{
			ble_evt_dispatch(bleEvt);
		}

		if (!noEvt)
		{
			break;
		}
	}
}

void SoftDeviceFaultHandl(uint32_t id, uint32_t pc, uint32_t info)
{

	DBG("\r\nFATAL_SOFTDEV");
	DBG("\r\nid: [0x%02X]; pc: [0x%02X]", (unsigned int)id, (unsigned int)pc);
	// On assert, the system can only recover with a reset.
#if 1	// nordic debug check overrided by me
    NVIC_SystemReset();
#else
    app_error_save_and_stop(id, pc, info);
#endif // DEBUG
}

