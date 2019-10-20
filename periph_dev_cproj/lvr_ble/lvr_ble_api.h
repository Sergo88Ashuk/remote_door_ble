/*
 * adv_test.h
 *
 *  Created on: 29 сент. 2018 г.
 *      Author: lvr_laptop
 */

#ifndef PERIPH_DEV_CPROJ_ADV_TEST_ADV_TEST_H_
#define PERIPH_DEV_CPROJ_ADV_TEST_ADV_TEST_H_


#include "../global_defs.h"
#include "../debug.h"

#define DOOR_HEALTH_SERVICE		(0)
#define HS_BATT_CHARAC			(0)
#define HS_ALIVE_WD_CHARAC		(1)

#define DOOR_LOCK_SERVICE		(1)
#define LS_GERCON_CHARAC		(0)
#define LS_RELAY_CHARAC			(1)

#define DOOR_PROX_SERVICE		(2)

#define DEV_NAME						"Hard_Shit"
#define APP_ADV_INTERVAL                (300)
#define IS_SRVC_CHANGED_CHARACT_PRESENT (1)

//void*   GetBleServer(void);

bool BLELVR_InitServer();

void 	StartSoftDevice(bool state);
void 	StartAdvert(bool state);
void    StartBleStack(bool state, uint16_t gattsSize);
void 	StartService(uint8_t servName, bool defParams);
void    StartCharact(uint8_t servName, uint8_t charactName, bool defParams);
uint8_t GetAttr(uint8_t servName, uint8_t characName);
void    SetAttr(uint8_t servName, uint8_t characName, uint32_t val);
void 	Dump(char* dumpItem, uint32_t vrbLvl);

#endif /* PERIPH_DEV_CPROJ_ADV_TEST_ADV_TEST_H_ */
