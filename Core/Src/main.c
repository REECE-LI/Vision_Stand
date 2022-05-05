/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
 /* USER CODE END Header */
 /* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stm32f4xx_hal_tim.h"
#include "config.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"
#include "stdio.h"
#include "rocker.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "testApp.h"
#include "startUp.h"
#include "Motor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
u32 ADC_Value[50];
u16 pscX;
u16 pscZ;
u16 tl;
u16 zCount = 0;
u16 xCount = 0;

//u32 pwm[10] = { 0 };
bool flagX = 1;
bool flagZ = 1;
//u8 pwmCount = 0;
//u8 count = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_SPI1_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

#if LVGL_RUN
  lv_init();
  lv_port_disp_init();  // 显示器初始化
  lv_port_indev_init(); //
#else
  LCD_Init();
  LCD_Fill(0, 0, 240, 240, WHITE);
  HAL_Delay(1000);
#endif

  //  for (tl = 0; tl < 10; tl++) {
  //    pwm[tl] = 499;
  //  }
  //  pwm[9] = 0;
    // printf("OK");
  tl = 0;
  pscX = 0;
  pscZ = 0;
  //  zCount = 0;
  //  xCount = 0;


  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  // HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
#if 1
//  HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwm, 10);
//  HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t *)pwm, 10000);
#else
  HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_4);
#endif

  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&ADC_Value, 50);
  // LCD_ShowPicture(0,0,240,240,gImage_we);

  // DMA_Fill(0,0,240,240,(u8*)gImage_we);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

#if LVGL_RUN
  startUp();
#endif

  HAL_TIM_Base_Start_IT(&htim3);


  while (1) {
    // 只是为了看一下CPU正真的利用率
#if LVGL_RUN
    lv_task_handler();
#if 1
    HAL_UART_Transmit(&huart1, (u8*)ADC_Value, 2, 10);
#endif
    getAd();
    if (!keyDir()) {
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
    }
#else
   // HAL_TIM_OnePulse_Start(&htim1, TIM_CHANNEL_1);
     //__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, plusX);
    // getAd();

     //HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwm, 100);
//  HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t *)pwm, 10);
//    if (!keyDir()) {
//      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
//      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
//			
//			HAL_TIM_Base_Stop_IT(&htim1);
//    }


//   HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwm, 100);

#endif

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
  RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
    | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
  if (htim->Instance == htim3.Instance) {
#if LVGL_RUN
    lv_tick_inc(1);
#else
#if 1
    getAd();
    doSth();
#else
    controlMotor();
#endif
    // LCD_ShowIntNum(0, 60, tl++, 4, BLACK, WHITE, 16);
#endif
  }
  //  else if (htim->Instance == htim1.Instance) {
  //    LCD_ShowIntNum(0, 5, tl++, 5, RED, WHITE, 16);
  //  }
    //	if (htim->Instance == htim1.Instance) {
    //		 LCD_ShowIntNum(0, 0, tl++, 4, BLACK, WHITE, 16);
    //	}
}

#if 1

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim) {
//  if (TIM_CHANNEL_STATE_GET(&htim1, TIM_CHANNEL_1) == HAL_TIM_CHANNEL_STATE_BUSY && \
//    TIM_CHANNEL_STATE_GET(&htim1, TIM_CHANNEL_4) != HAL_TIM_CHANNEL_STATE_BUSY) {
//    if (flagX == 1) {
//      if (xCount < XMAX - 10) {
//        xCount++;
//        LCD_ShowIntNum(0, 5, xCount, 10, RED, WHITE, 16);
//      }
//      else HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
//    }
//    else {
//      if (xCount > 0) {
//        xCount--;
//        LCD_ShowIntNum(0, 5, xCount, 10, RED, WHITE, 16);
//      }
//      else HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
//    }
//  }


//  if (TIM_CHANNEL_STATE_GET(&htim1, TIM_CHANNEL_4) == HAL_TIM_CHANNEL_STATE_BUSY && \
//    TIM_CHANNEL_STATE_GET(&htim1, TIM_CHANNEL_1) != HAL_TIM_CHANNEL_STATE_BUSY) {
//    
//    if (flagZ == 1) {
//      if (zCount < ZMAX - 10) {
//        zCount++;
//        LCD_ShowIntNum(0, 25, zCount, 10, RED, WHITE, 16);
//      }
//      else HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
//    }
//    else {
//      if (zCount > 0) {
//        zCount--;
//        LCD_ShowIntNum(0, 25, zCount, 10, RED, WHITE, 16);
//      }
//      else HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
//    }
//  }


//  if (TIM_CHANNEL_STATE_GET(&htim1, TIM_CHANNEL_4) == HAL_TIM_CHANNEL_STATE_BUSY && \
//    TIM_CHANNEL_STATE_GET(&htim1, TIM_CHANNEL_1) == HAL_TIM_CHANNEL_STATE_BUSY) {
//	if (htim->Channel == TIM_CHANNEL_3)	{
//			if (flagZ == 1) {
//      if (zCount < ZMAX - 10) {
//        zCount++;
//        LCD_ShowIntNum(0, 25, zCount, 10, RED, WHITE, 16);
//      }
//      else HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
//    }
//    else {
//      if (zCount > 0) {
//        zCount--;
//        LCD_ShowIntNum(0, 25, zCount, 10, RED, WHITE, 16);
//      }
//      else HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
//    }
//	}	
//    
//	if (htim->Channel == TIM_CHANNEL_2) {
//		if (flagX == 1) {
//      if (xCount < XMAX - 10) {
//        xCount++;
//        LCD_ShowIntNum(0, 5, xCount, 10, RED, WHITE, 16);
//      }
//      else HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
//    }
//    else {
//      if (xCount > 0) {
//        xCount--;
//        LCD_ShowIntNum(0, 5, xCount, 10, RED, WHITE, 16);
//      }
//      else HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
//    }
//		xCount = zCount;
//	}
//    
//  }
if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2 && \
	htim->Channel != HAL_TIM_ACTIVE_CHANNEL_3) {
		if (flagX == 1) {
      if (xCount < XMAX - 10) {
        xCount++;
        LCD_ShowIntNum(0, 5, xCount, 10, RED, WHITE, 16);
      }
      else HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
    }
    else {
      if (xCount > 0) {
        xCount--;
        LCD_ShowIntNum(0, 5, xCount, 10, RED, WHITE, 16);
      }
      else HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
    }
		//xCount = zCount;
	}

	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3 && \
		htim->Channel != HAL_TIM_ACTIVE_CHANNEL_2)	{
			if (flagZ == 1) {
      if (zCount < ZMAX - 10) {
        zCount++;
        LCD_ShowIntNum(0, 25, zCount, 10, RED, WHITE, 16);
      }
      else HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
    }
    else {
      if (zCount > 0) {
        zCount--;
        LCD_ShowIntNum(0, 25, zCount, 10, RED, WHITE, 16);
      }
      else HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
    }
	}	



}
#endif

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1) {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line) {
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
     /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
