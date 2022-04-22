#include "exit.h"
#include "usart.h"

#if 0
/**
 * @Name: HAL_GPIO_EXTI_Callback
 * @Description: 外部中断回调 中断消抖
 * @Author: 李明骏
 * @Return: 
 * @Date: 2022-03-04 19:14:50
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) 
{
    if(GPIO_Pin == exKey_Pin) // 外部触发
    {
      HAL_Delay(1000);
     if (HAL_GPIO_ReadPin(exKey_GPIO_Port, exKey_Pin) == GPIO_PIN_RESET)
      {
				while(HAL_GPIO_ReadPin(exKey_GPIO_Port, exKey_Pin) == GPIO_PIN_RESET);
				printf("[ info] exinit OK! \r\n");
      }
    }
}

// 基本消抖模板 也可用作开关机延时检测
#if 0
if(GPIO_Pin == exKey_Pin) // 外部触发
    {
      HAL_Delay(1000);
     if (HAL_GPIO_ReadPin(exKey_GPIO_Port, exKey_Pin) == GPIO_PIN_RESET)
      {
				while(HAL_GPIO_ReadPin(exKey_GPIO_Port, exKey_Pin) == GPIO_PIN_RESET);
				printf("[ info] exinit OK! \r\n");
      }
    }
#endif

#endif

