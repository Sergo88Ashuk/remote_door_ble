/*
 * lvr_error_handling.c
 *
 *  Created on: 20 ���. 2018 �.
 *      Author: lvr_laptop
 */

#include "../lvr_errh/lvr_errh.h"

#define NRF_ERROR_BASE_NUM      (0x0)       ///< Global error base
#define NRF_ERROR_SDM_BASE_NUM  (0x1000)    ///< SDM error base
#define NRF_ERROR_SOC_BASE_NUM  (0x2000)    ///< SoC error base
#define NRF_ERROR_STK_BASE_NUM  (0x3000)    ///< STK error base

#define NRF_SUCCESS                           (NRF_ERROR_BASE_NUM + 0)  ///< Successful command
#define NRF_ERROR_SVC_HANDLER_MISSING         (NRF_ERROR_BASE_NUM + 1)  ///< SVC handler is missing
#define NRF_ERROR_SOFTDEVICE_NOT_ENABLED      (NRF_ERROR_BASE_NUM + 2)  ///< SoftDevice has not been enabled
#define NRF_ERROR_INTERNAL                    (NRF_ERROR_BASE_NUM + 3)  ///< Internal Error
#define NRF_ERROR_NO_MEM                      (NRF_ERROR_BASE_NUM + 4)  ///< No Memory for operation
#define NRF_ERROR_NOT_FOUND                   (NRF_ERROR_BASE_NUM + 5)  ///< Not found
#define NRF_ERROR_NOT_SUPPORTED               (NRF_ERROR_BASE_NUM + 6)  ///< Not supported
#define NRF_ERROR_INVALID_PARAM               (NRF_ERROR_BASE_NUM + 7)  ///< Invalid Parameter
#define NRF_ERROR_INVALID_STATE               (NRF_ERROR_BASE_NUM + 8)  ///< Invalid state, operation disallowed in this state
#define NRF_ERROR_INVALID_LENGTH              (NRF_ERROR_BASE_NUM + 9)  ///< Invalid Length
#define NRF_ERROR_INVALID_FLAGS               (NRF_ERROR_BASE_NUM + 10) ///< Invalid Flags
#define NRF_ERROR_INVALID_DATA                (NRF_ERROR_BASE_NUM + 11) ///< Invalid Data
#define NRF_ERROR_DATA_SIZE                   (NRF_ERROR_BASE_NUM + 12) ///< Data size exceeds limit
#define NRF_ERROR_TIMEOUT                     (NRF_ERROR_BASE_NUM + 13) ///< Operation timed out
#define NRF_ERROR_NULL                        (NRF_ERROR_BASE_NUM + 14) ///< Null Pointer
#define NRF_ERROR_FORBIDDEN                   (NRF_ERROR_BASE_NUM + 15) ///< Forbidden Operation
#define NRF_ERROR_INVALID_ADDR                (NRF_ERROR_BASE_NUM + 16) ///< Bad Memory Address
#define NRF_ERROR_BUSY                        (NRF_ERROR_BASE_NUM + 17) ///< Busy

const char* errTableApp[] =
{
	"NRF_SUCCESS",
	"NRF_ERROR_SVC_HANDLER_MISSING",
	"NRF_ERROR_SOFTDEVICE_NOT_ENABLED",
	"NRF_ERROR_INTERNAL",
	"NRF_ERROR_NO_MEM",
	"NRF_ERROR_NOT_FOUND",
	"NRF_ERROR_NOT_SUPPORTED",
	"NRF_ERROR_INVALID_PARAM",
	"NRF_ERROR_INVALID_STATE",
	"NRF_ERROR_INVALID_LENGTH",
	"NRF_ERROR_INVALID_FLAGS",
	"NRF_ERROR_INVALID_DATA",
	"NRF_ERROR_DATA_SIZE",
	"NRF_ERROR_TIMEOUT",
	"NRF_ERROR_NULL",
	"NRF_ERROR_FORBIDDEN",
	"NRF_ERROR_INVALID_ADDR",
	"NRF_ERROR_BUSY",
};

void LVREH_PrintErrorCode(uint32_t errC)
{
	DBG("\r\n[0x%02X] [%s]", (unsigned int) errC, errTableApp[errC]);
}

void AppErrorHandl(uint32_t id, uint32_t pc, AppError* info)
{

	DBG("\r\n***FATAL_from_app***");
	DBG("\r\n%s: %u", info->file, (unsigned int) info->line);
	LVREH_PrintErrorCode(info->errC);
	DBG("\r\nforever looped...");
//	DBG("\r\nid: [0x%02X]; pc: [0x%02X]", (unsigned int)id, (unsigned int)pc);
    //for(;;);
	NVIC_SystemReset();
}


