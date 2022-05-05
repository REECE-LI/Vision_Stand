/*
 * @Description: 按键函数
 * @Version: 1.0
 * @Author: 李明骏
 * @Date: 2022-03-02 17:33:51
 */
#include "key.h"
//#include "usart.h"


/**
 * @Name: pressJudg
 * @Description: 按键简单判断
 * @Author: 李明骏
 * @Return: 1 按下；0 没按下
 * @Date: 2022-03-03 14:46:07
 */

u8 pressJudg(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET)
    {
        HAL_Delay(5);
        if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET)
        {
            while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET);
            return 1;
        }
        return 0;
    }
    return 0;
}


/**
 * @Name: pressJudg_R
 * @Description: 按键简单判断
 * @Author: 李明骏
 * @Return: 1 按下；0 没按下
 * @Date: 2022-03-03 14:46:07
 */

u8 pressJudg_R(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET)
    {
        // HAL_Delay(10);
        // if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_SET)
        while(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET)
        {
            lv_task_handler();
        }
            return 1;
        // }
        // return 0;
    }
    return 0;
}

/**
 * @Name: scanKey
 * @Description: 按键扫描
 * @Author: 李明骏
 * @Return: 具体按键值 正常不用 
 * @Date: 2022-03-04 08:11:33
 */
#if keyScan
u8 scanKey(void)
{
    u8 keyValue = 0;
    switch (1)
    {
    case pressJudg():
        keyValue = 1;
        break;
    
    default:
        break;
    }
}
#endif
