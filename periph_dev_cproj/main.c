
/** @file
 *
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example
 * @brief Blinky Example Application main file.
 *
 * This file contains the source code for a sample application to blink LEDs.
 *
 */

#include "app/cmd_line/cmd_line.h"
#include "global_defs.h"
#include "terminal/terminal.h"
#include "lvr_gpio.h"
#include "lvr_uart.h"
#include "lvr_adc.h"
#include "app/cmd_line/cmd_line.h"
#include "app/stand_alone/stand_alone.h"
#include "debug.h"


#define CLI_MODE	(1)
#define LOOP_MODE	(0)
#define EXEC_MODE	LOOP_MODE
/**
 * @brief Function for application main entry.
 */

//static char startSym;

int main(void)
{
   char buf2[2];
   setvbuf(stdout, buf2, _IONBF, 2);
   UARTLVR_Init(5, 4, 0x0275000); //todo: remove magic
   UARTLVR_Start();
   GPIOLVR_Init(GPIO_8, true);
   GPIOLVR_Init(GPIO_10, false);
   GPIOLVR_Init(GPIO_11, true);
   ADCLVR_Init();

   STALN_App();

//   if(UARTLVR_GetSym() == 't') {CMDL_Start();}
//   else						   {STALN_App();}
}




/**
 *@}
 **/

