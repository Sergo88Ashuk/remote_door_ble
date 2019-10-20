/*
 * adv_test.c
 *
 *  Created on: 29 сент. 2018 г.
 *      Author: lvr_laptop
 */

#include "lvr_ble_low.h"
#include "lvr_ble_api.h"

static LVR_Ble_Server /*const*/ LVR_bleServer;
ble_uuid128_t vsUuid[] =
{
		{{0x2E, 0xB3, 0x4E, 0x53,
		  0x7B, 0xB4, 0x8B, 0xA5,
		  0x6D, 0x42, 0x9B, 0x3A,
		  0x00, 0x00, 0x78, 0xAB}},
		{{0x2C, 0xB3, 0x4E, 0x53,
		  0x7B, 0xB4, 0x8B, 0xA5,
		  0x6D, 0x42, 0x9B, 0x3A,
		  0x00, 0x00, 0x78, 0xAB}},
		{{0x28, 0xB3, 0x4E, 0x53,
		  0x7B, 0xB4, 0x8B, 0xA5,
		  0x6D, 0x42, 0x9B, 0x3A,
		  0x00, 0x00, 0x78, 0xAB}}
};

static uint16_t characUuid[] =
{
	0x1525,
	0x1625,
	0x1725
};

//void* GetBleServer(void)
//{
//	return LVR_bleServer;
//}

void StartService(uint8_t servName, bool defParams)
{
	if (defParams)
	{
		LVR_bleServer.service[servName].servUuid.uuid128 = vsUuid[servName];
		LVR_bleServer.service[servName].handle  = servName;
		AddUuid(&LVR_bleServer.service[servName].servUuid);

		LVR_bleServer.service[servName].servType = BLE_GATTS_SRVC_TYPE_PRIMARY;
		AddService(&LVR_bleServer.service[servName]);
	}
}

uint8_t GetAttr(uint8_t servName, uint8_t characName)
{
	LVR_Charac* charac = &LVR_bleServer.service[servName].charact[characName];
	return SdGetAttr(charac);
}

void SetAttr(uint8_t servName, uint8_t characName, uint32_t val)
{
	uint8_t attrVal = (uint8_t) val;
	LVR_Charac* charac = &LVR_bleServer.service[servName].charact[characName];
	SdSetAttr(charac, &attrVal);
}

void StartSoftDevice(bool state)
{
	LVR_Softdevice_Params* sdP = &LVR_bleServer.softDev;

	sdP->clock.rc_ctiv = 0;
	sdP->clock.rc_temp_ctiv = 0;
	sdP->clock.source = NRF_CLOCK_LF_SRC_XTAL;
	sdP->clock.xtal_accuracy = NRF_CLOCK_LF_XTAL_ACCURACY_20_PPM;
	sdP->softDevFaultHandler = SoftDeviceFaultHandl;
	sdP->sdState = state;

	EnableSoftDevice(&LVR_bleServer.softDev);
}

void StartBleStack(bool state, uint16_t gattsSize)
{
	ble_enable_params_t* bleP = &LVR_bleServer.bleStack.bleModule;
	memset(bleP, 0, sizeof(*bleP));

	if (state)
	{	// applying default parameters
		bleP->gatts_enable_params.service_changed = IS_SRVC_CHANGED_CHARACT_PRESENT;
		bleP->gatts_enable_params.attr_tab_size = gattsSize;
		bleP->gap_enable_params.periph_conn_count = 1;
	}
	else
	{
		bleP->gatts_enable_params.attr_tab_size = BLE_GATTS_ATTR_TAB_SIZE_MIN;
	}

	EnableBleStack(&LVR_bleServer.bleStack);
}

void StartCharact(uint8_t servName, uint8_t charactName, bool defParams)
{
	LVR_Charac* chP = &LVR_bleServer.service[servName].charact[charactName];

	memset(&chP->char_md, 0, sizeof(chP->char_md));
	memset(&chP->attr_md, 0, sizeof(chP->attr_md));
	memset(&chP->attr_char_value, 0, sizeof(chP->attr_char_value));

	chP->char_md.char_props.read   = 1;
	chP->char_md.char_props.write  = 1;
	chP->char_md.p_char_user_desc  = NULL;
	chP->char_md.p_char_pf         = NULL;
	chP->char_md.p_user_desc_md    = NULL;
	chP->char_md.p_cccd_md         = NULL;
	chP->char_md.p_sccd_md         = NULL;

	chP->ble_uuid.type = LVR_bleServer.service[servName].servUuid.uuid16.type;
	chP->ble_uuid.uuid = characUuid[servName] + charactName;

	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&chP->attr_md.read_perm);
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&chP->attr_md.write_perm);
	chP->attr_md.vloc       = BLE_GATTS_VLOC_STACK;
	chP->attr_md.rd_auth    = 0;
	chP->attr_md.wr_auth    = 0;
	chP->attr_md.vlen       = 0;

	chP->attr_char_value.p_uuid       = &chP->ble_uuid;
	chP->attr_char_value.p_attr_md    = &chP->attr_md;
	chP->attr_char_value.init_len     = sizeof(uint8_t);
	chP->attr_char_value.init_offs    = 0;
	chP->attr_char_value.max_len      = sizeof(uint8_t);
	chP->attr_char_value.p_value      = NULL;

	AddCharac(&LVR_bleServer.service[servName].charact[charactName],\
			   LVR_bleServer.service[servName].handle);
}

void StartAdvert(bool state)
{
	LVR_Advert_Mode* adM = &LVR_bleServer.advParams;
	memset(&adM->advData, 0, sizeof(adM->advData));
	memset(&adM->advParam, 0, sizeof(adM->advParam));

	adM->state = state;
	adM->devName = DEV_NAME;
	adM->devNameLen = strlen(adM->devName);
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&adM->secMode);

	adM->advData.name_type		         = BLE_ADVDATA_FULL_NAME;
	adM->advData.include_appearance	     = true;
	adM->advData.flags				     = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
	adM->advData.uuids_complete.uuid_cnt = sizeof(&adM->advUuid) / sizeof(adM->advUuid[0]);
	adM->advData.uuids_complete.p_uuids  = adM->advUuid;

	adM->advParam.type 	   = BLE_GAP_ADV_TYPE_ADV_IND;
	adM->advParam.fp	   = BLE_GAP_ADV_FP_ANY;
	adM->advParam.interval = APP_ADV_INTERVAL;
	adM->advParam.timeout  = 0;

	adM->txPower = 4; // TODO: remove magic

	EnableAdvert(&LVR_bleServer.advParams);
}

void Dump(char* dumpItem, uint32_t vrbLvl)
{

}

bool BLELVR_InitServer()
{
	bool result = true;

	// switch sd on
	StartSoftDevice(true);

	//config ble stack
	StartBleStack(true, 600);

	//add service
	StartService(DOOR_HEALTH_SERVICE, true); //may be better todo inside
											// bsp modules

	//add characteristic
	StartCharact(DOOR_HEALTH_SERVICE, HS_BATT_CHARAC, true);
//	StartCharact(DOOR_HEALTH_SERVICE, HS_ALIVE_WD_CHARAC, true);

	StartService(DOOR_LOCK_SERVICE, true);	//may be better todo inside
											// bsp modules

	StartCharact(DOOR_LOCK_SERVICE, LS_GERCON_CHARAC, true);
	StartCharact(DOOR_LOCK_SERVICE, LS_RELAY_CHARAC, true);

	return result;
}
