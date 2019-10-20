/*
 * lvr_ble.h
 *
 *  Created on: 13 окт. 2018 г.
 *      Author: lvr_laptop
 */

#ifndef PERIPH_DEV_CPROJ_LVR_BLE_LVR_BLE_LOW_H_
#define PERIPH_DEV_CPROJ_LVR_BLE_LVR_BLE_LOW_H_

#include "../global_defs.h"
#include "../debug.h"

#define MAX_SERVICE_NUM			(3)
#define MAX_CHARAC_NUM			(2)

typedef  void (*int_handler_sd)(uint32_t, uint32_t, uint32_t);

typedef struct
{
	bool				sdState;
	nrf_clock_lf_cfg_t  clock;
	int_handler_sd		softDevFaultHandler;
}LVR_Softdevice_Params;

typedef struct
{
	ble_enable_params_t bleModule;
}LVR_BleStack_Params;

typedef struct
{
	ble_uuid128_t	uuid128;
	ble_uuid_t 		uuid16;
}LVR_Service_Uuid;

typedef struct
{
	char*					 characName;
	ble_gatts_char_md_t 	 char_md;
	ble_gatts_attr_t    	 attr_char_value;
	ble_uuid_t          	 ble_uuid;
	ble_gatts_attr_md_t 	 attr_md;
	ble_gatts_char_handles_t char_handles;
}LVR_Charac;

typedef struct
{
	uint8_t 			servType;
	LVR_Service_Uuid	servUuid;
	uint16_t 			handle;
	char*				servName;
	LVR_Charac			charact[MAX_CHARAC_NUM];
}LVR_Service;

typedef struct
{
	bool 					state;
	const char*				devName;
	uint32_t				devNameLen;
	int8_t					txPower;
	ble_advdata_t 		    advData;
	ble_gap_adv_params_t    advParam;
	ble_gap_conn_sec_mode_t secMode;
	ble_uuid_t 			    advUuid[];
}LVR_Advert_Mode;

typedef struct
{
	LVR_Softdevice_Params	softDev;
	LVR_BleStack_Params		bleStack;
	LVR_Advert_Mode			advParams;
	LVR_Service				service[MAX_SERVICE_NUM];
}LVR_Ble_Server;

bool EnableSoftDevice(LVR_Softdevice_Params* enableParams);
bool EnableBleStack(LVR_BleStack_Params* enableParams);
bool AddUuid(LVR_Service_Uuid* servUuid);
bool AddService(LVR_Service* service);
void AddCharac(LVR_Charac* charac, uint16_t handle);
void EnableAdvert(LVR_Advert_Mode* advMode);
void SoftDeviceFaultHandl(uint32_t id, uint32_t pc, uint32_t info);
uint8_t SdGetAttr(LVR_Charac* charac);
void    SdSetAttr(LVR_Charac* charac, uint8_t* val);

#endif /* PERIPH_DEV_CPROJ_LVR_BLE_LVR_BLE_LOW_H_ */
