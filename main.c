/************************************************************************
 * 			uLipeTemplate Project for Atollic TrueSTUDIO
 *			This was originaly done for STM32F429I-DISCO
 *		to others processors and boards you can add in HAL.h
 *
 *
 *
 *	# uLipeRtosV4
 *
 * uLipeRTOS Version 4 is a simple, but powerful real time kernel,
 * currently implemented for arm cortex M0,M3,M4 and M7 processors.
 * The kernel uses a fully preemptive schedule policy,
 * and supports up to 1024 priority levels.
 *
 * Main features:
 * - Real time, preemptive kernel;
 * - Fast context switching time, below to 100ns @ 50MHz processor clock;
 * - Fully configurable thru a config header file;
 * - Supports up to 1024 priority levels;
 * - Event flag groups, up to 32bits events;
 * - Counting semaphores;
 * - Binary semaphores;
 * - Queueing by reference support;
 * - Port file formed by two simple files in C and Assembly, simple to port;
 * - Unlimited kernel objects (limited by processor memory);
 * - Run time creation objects;
 * - Except port file, implementend in fully ANSI-C.
 ***********************************************************************/

#include "main.h"

int main(void)
{
	HAL_Init();
	/* Configure the System clock to 180 MHz */
	SystemClock_Config();
	uLipeRtosInit();
	// Load the stacks
	OsStack_t Stack1[48],Stack2[48];
	//Create the RTOS stack pointers
	OsStackPtr_t pStack1 = &Stack1;
	OsStackPtr_t pStack2 = &Stack2;
	//Create the RTOS tasks
	uLipeTaskCreate( Task1, pStack1, 48, 1, NULL);
	uLipeTaskCreate( Task2, pStack2, 48, 2, NULL);
	//Start the scheduler
	uLipeRtosStart();
	while(1){}

}
//Dummy Task1
void Task1(void)
{
	while(1)
	{
		uLipeTaskDelay(1000);
	}
}
//Dummy Task2
void Task2(void)
{
	while(1)
	{
		uLipeTaskDelay(1000);
	}
}
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
