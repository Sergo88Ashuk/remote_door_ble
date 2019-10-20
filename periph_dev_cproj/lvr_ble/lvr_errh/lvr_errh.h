/*
 * lvr_error_handling.h
 *
 *  Created on: 20 окт. 2018 г.
 *      Author: lvr_laptop
 */

#ifndef PERIPH_DEV_CPROJ_LVR_BLE_LVR_ERROR_HANDLING_H_
#define PERIPH_DEV_CPROJ_LVR_BLE_LVR_ERROR_HANDLING_H_

#include "../../global_defs.h"
#include "../../debug.h"


typedef struct
{
	uint32_t    line;
	const char* file;
	uint32_t 	errC;
}AppError;

void LVREH_PrintErrorCode(uint32_t errC);
void AppErrorHandl(uint32_t id, uint32_t pc, AppError* info);

#define _APP_ERROR_CHECK(errCode)							\
{															\
	uint32_t errC = errCode;								\
	if (errC != NRF_SUCCESS)								\
	{														\
		AppError appErr =									\
	    {													\
	        .line    = __LINE__,							\
	        .file    = __FILE__,							\
	        .errC     = errC,								\
	    };													\
	    AppErrorHandl(NRF_FAULT_ID_SDK_ERROR, 0, &appErr); \
	}														\
}

#endif /* PERIPH_DEV_CPROJ_LVR_BLE_LVR_ERROR_HANDLING_H_ */
