/*
 * @Description: 从LVGL内部跳转至这
 * @Version: 1.0
 * @Author: 李明骏
 * @Date: 2022-04-28 17:10:04
 */
#include "Motor.h"
 // #include "stm32f4xx_hal_tim.h"


extern Site screenSite;
extern u16 pscX;
extern u16 pscZ;
extern TIM_HandleTypeDef htim1;

extern u8 flagX;
extern u8 flagZ;
/**
 * @Name: switchDir
 * @Description: 方向上的选择 0:向左向下，1：向右向上  电机上选择 0：x；1：Z
 * @ X轴方向为960；Z轴方向3400
 * @Author: 李明骏
 * @Return:
 * @Date: 2022-05-02 11:03:13
 * @param {u8} which
 * @param {u16} psc
 */
void switchDir(u8 which, u8 dir) {
    switch (which) {
    case 0:
        // 先进行方向的筛选
        if (dir == 0)
            HAL_GPIO_WritePin(xDir_GPIO_Port, xDir_Pin, GPIO_PIN_RESET);
        else
            HAL_GPIO_WritePin(xDir_GPIO_Port, xDir_Pin, GPIO_PIN_SET);
        break;
    case 1:
        if (dir == 0)
            HAL_GPIO_WritePin(zDir_GPIO_Port, zDir_Pin, GPIO_PIN_SET);
        else

            HAL_GPIO_WritePin(zDir_GPIO_Port, zDir_Pin, GPIO_PIN_RESET);
        break;
    default:
        break;
    }
}
extern u16 zCount;
extern u16 xCount;
void controlMotor(void) {
    getAd();
    switch (keyDir()) {
    case up:
        if (1) {
            if (1) {
#if 1
                LCD_ShowIntNum(120, 120, 1, 1, BLACK, WHITE, 16);
                //LCD_ShowIntNum(0, 20, zCount++, 4, BLACK, WHITE, 16);
#endif    

                switchDir(1, 1);
                pscZ = (u16)(100 + screenSite.y_now * 7.5);
                __HAL_TIM_SET_PRESCALER(&htim1, pscZ);
                HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_4);
                //flagZ = 0;
            }
        }
        break;
    case down:
        if (1) {
            if (1) {
#if 1
                LCD_ShowIntNum(120, 120, 2, 1, BLACK, WHITE, 16);
                //LCD_ShowIntNum(0, 20, zCount--, 4, BLACK, WHITE, 16);
#endif
                switchDir(1, 0);
                pscZ = (u16)(1900 - screenSite.y_now * 7.5);
                __HAL_TIM_SET_PRESCALER(&htim1, pscZ);
                HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_4);
                //flagZ = 0;
            }
        }
        break;
    case left:
        if (1) {
            if (1) {
#if 1
                LCD_ShowIntNum(120, 120, 3, 1, BLACK, WHITE, 16);
                //LCD_ShowIntNum(0, 0, xCount++, 4, BLACK, WHITE, 16);
#endif
                switchDir(0, 0);
                pscX = (u16)(100 + screenSite.x_now * 7.5);
                __HAL_TIM_SET_PRESCALER(&htim1, pscX);
                HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
                // flagX = 0;
            }
        }
        break;
    case right:
        if (1) {
            if (1) {
#if 1
                LCD_ShowIntNum(120, 120, 4, 1, BLACK, WHITE, 16);
                //LCD_ShowIntNum(0, 0, xCount--, 4, BLACK, WHITE, 16);
#endif
                switchDir(0, 1);
                pscX = (u16)(1900 - screenSite.x_now * 7.5);
                __HAL_TIM_SET_PRESCALER(&htim1, pscX);
                HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
                //flagX = 0;
            }
        }
        break;
    case up_left:
        LCD_ShowIntNum(120, 120, 5, 1, BLACK, WHITE, 16);
        switchDir(0, 0);
        switchDir(1, 1);
        pscX = (u16)(100 + screenSite.x_now * 7.5);
        pscZ = (u16)(100 + screenSite.y_now * 7.5);
        __HAL_TIM_SET_PRESCALER(&htim1, (pscZ + pscX) / 2);
        if (1) {
            if (1) {
                //LCD_ShowIntNum(120, 120, 3, 1, BLACK, WHITE, 16);
                //LCD_ShowIntNum(0, 0, xCount++, 4, BLACK, WHITE, 16);
                HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
                //flagX = 0;
            }
        }
        if (1) {
            if (1) {
                // LCD_ShowIntNum(0, 20, zCount++, 4, BLACK, WHITE, 16);
                HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_4);
                //flagZ = 0;
            }
        }
        break;
    case up_right:
        if (1) {
            if (1) {
#if 1
                LCD_ShowIntNum(120, 120, 6, 1, BLACK, WHITE, 16);
                //                LCD_ShowIntNum(0, 0, xCount--, 4, BLACK, WHITE, 16);
                //                LCD_ShowIntNum(0, 20, zCount++, 4, BLACK, WHITE, 16);
#endif
                // 选择轴向 控制方向
                switchDir(1, 1);
                //设置频率 调节速度
                pscZ = (u16)(100 + screenSite.y_now * 7.5);
                switchDir(0, 1);
                pscX = (u16)(1900 - screenSite.x_now * 7.5);
                __HAL_TIM_SET_PRESCALER(&htim1, pscX);
//                HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)pwm, 5);
//                HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t*)pwm, 5);
                flagX = 0;
            }
        }
        break;
    case down_right:
        if (1) {
            if (1) {
#if 1
                LCD_ShowIntNum(120, 120, 8, 1, BLACK, WHITE, 16);
                //                LCD_ShowIntNum(0, 0, xCount--, 4, BLACK, WHITE, 16);
                //                LCD_ShowIntNum(0, 20, zCount--, 4, BLACK, WHITE, 16);
#endif
                switchDir(1, 0);
                pscZ = (u16)(1900 - screenSite.y_now * 7.5);
                switchDir(0, 1);
                HAL_GPIO_WritePin(xDir_GPIO_Port, xDir_Pin, GPIO_PIN_SET);
                pscX = (u16)(1900 - screenSite.x_now * 7.5);
                __HAL_TIM_SET_PRESCALER(&htim1, pscX);
//                HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)pwm, 5);
//                HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t*)pwm, 5);
                flagX = 0;
            }
        }
        break;
    case down_left:
        if (1) {
            if (1) {
#if 1
                LCD_ShowIntNum(120, 120, 7, 1, BLACK, WHITE, 16);
                //                LCD_ShowIntNum(0, 0, xCount++, 4, BLACK, WHITE, 16);
                //                LCD_ShowIntNum(0, 20, zCount--, 4, BLACK, WHITE, 16);
#endif
                switchDir(1, 0);
                pscZ = (u16)(1900 - screenSite.y_now * 7.5);
                switchDir(0, 0);
                pscX = (u16)(100 + screenSite.x_now * 7.5);
                __HAL_TIM_SET_PRESCALER(&htim1, pscX);
//                HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)pwm, 5);
//                HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t*)pwm, 5);
                flagX = 0;
            }
        }
        break;
    case press:
        // LCD_ShowIntNum(120, 120, 9, 1, BLACK, WHITE, 16);
        break;
    default:
        LCD_ShowIntNum(120, 120, 0, 1, BLACK, WHITE, 16);
        HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_4);
        HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1);
        flagX = 1;
        flagZ = 1;
        // 直接设置占空比为0 中位时停止 转动
     //        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
     //        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
        break;
    }

}
#if 0
u32 countX = 0;
u32 countZ = 0;
// HAL_TIM_PWM_PulseFinishedCallback  HAL_TIM_TriggerCallback
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim) {
    LCD_ShowIntNum(0, 0, countX, 10, RED, WHITE, 16);
    if (htim->Instance == htim1.Instance) {
        if (htim->Channel == TIM_CHANNEL_1) {
            countX++;
#if 1
            LCD_ShowIntNum(0, 0, countX, 10, RED, WHITE, 16);
#endif
        }
    }

}

#endif

