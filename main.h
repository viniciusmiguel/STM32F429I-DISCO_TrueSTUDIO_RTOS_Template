/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "uLipeRtos4.h"
#include "HAL.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
static void SystemClock_Config(void);
static void Error_Handler(void);
void Task1(void);
void Task2(void);
#endif /* __MAIN_H */

/******************************************************************************/
