/*
 * @Description: 摇杆毕设
 * @Version: 1.0
 * @Author: 李明骏
 * @Date: 2022-04-14 22:55:38
 */
#include "rocker.h"
#include "key.h"
#include "main.h"
#include "stdio.h"
#include "config.h"
#include "motor.h"

extern u16 pscX;
extern u16 pscZ;
extern TIM_HandleTypeDef htim1;


extern u16 zCount;
extern u16 xCount;

extern u8 flagX;
extern u8 flagZ;
/**
 * @Name: modeJude
 * @Description: 摇杆模式
 * @Author: 李明骏
 * @Return: 连续型 非连续型
 * @Date: 2022-04-15 10:10:16
 */
mode_t modeJude(void) {
    if (1) {
        return linear;
    }
    else
        return noLinear;
}

Site screenSite;
void getAd(void) {
    // 此处调试 有个BUG 不可以使用LVGL 宏定义来进行调试 具体原因？？？
    // 否则无法进入 while大循环
    u8 i;
    float ady, adx;
    u8 x, y;
    for (i = 0, ady = 0, adx = 0; i < 50;) {
        ady += ADC_Value[i++];
        adx += ADC_Value[i++];
    }
    ady = ady / 25.0 * 3.3 / 4096;
    adx = adx / 25.0 * 3.3 / 4096;

#if 0
    x = adx * 10;
    y = ady * 10;

    adx = (float)x * 0.1;
    ady = (float)y * 0.1;
#else
    adx = adx / 3.3 * 240;
    ady = ady / 3.3 * 240;
#endif

    //#if LVGL_RUN == 0
    //    LCD_ShowFloatNum1(0, 0, adx, 10, BLACK, WHITE, 16);
    //    LCD_ShowFloatNum1(0, 20, ady, 10, BLACK, WHITE, 16);

    ////    screenSite.x_last = screenSite.x_now;
    ////    screenSite.y_last = screenSite.y_now;
    ////    screenSite.x_now = adx;
    ////    screenSite.y_now = ady;
    ////    LCD_DrawLine(screenSite.x_last, screenSite.y_last, screenSite.x_now, screenSite.y_now, RED);
    //#endif

    screenSite.x_last = screenSite.x_now;
    screenSite.y_last = screenSite.y_now;
    screenSite.x_now = adx;
    screenSite.y_now = ady;
}

/**
 * @Name: dir_t keyDir(void);
 * @Description: 判断方向 8个方向 20个像素点的死区
 * @Author: 李明骏
 * @Return:
 * @Date: 2022-04-15 11:07:18
 */
dir_t keyDir(void) {
    static u8 P;
    P = pressJudg_R(PRESS_GPIO_Port, PRESS_Pin);
    if (P)
        return press;
    if (screenSite.x_now < MIDDLE - SWITCHJUDG && screenSite.y_now > MIDDLE - DRIFT && screenSite.y_now < MIDDLE + DRIFT) {
#if 0
        pscX = (u16)(100 + screenSite.x_now * 7.5);
#endif
        // LCD_ShowIntNum(0, 40, pscX, 3, BLACK, WHITE, 16);
        //  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,499);
        return left;
    }

    else if (screenSite.x_now > MIDDLE + SWITCHJUDG && screenSite.y_now > MIDDLE - DRIFT && screenSite.y_now < MIDDLE + DRIFT) {
#if 0
        pscX = (u16)(1900 - screenSite.x_now * 7.5);
#endif
        // LCD_ShowIntNum(0, 40, pscX, 3, BLACK, WHITE, 16);
        //  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,499);
        return right;
    }

    else if (screenSite.x_now < MIDDLE + DRIFT && screenSite.x_now > MIDDLE - DRIFT && screenSite.y_now < MIDDLE - SWITCHJUDG)
        return up;
    else if (screenSite.x_now < MIDDLE + DRIFT && screenSite.x_now > MIDDLE - DRIFT && screenSite.y_now > MIDDLE + SWITCHJUDG)
        return down;
    else if (screenSite.x_now < MIDDLE - SWITCHJUDG && screenSite.y_now < MIDDLE - SWITCHJUDG)
        return up_left;
    else if (screenSite.x_now > MIDDLE + SWITCHJUDG && screenSite.y_now < MIDDLE - SWITCHJUDG)
        return up_right;
    else if (screenSite.x_now > MIDDLE + SWITCHJUDG && screenSite.y_now > MIDDLE + SWITCHJUDG)
        return down_right;
    else if (screenSite.x_now < MIDDLE - SWITCHJUDG && screenSite.y_now > MIDDLE + SWITCHJUDG)
        return down_left;
    // else if (pressJudg(PRESS_GPIO_Port, PRESS_Pin))
    // return press;
    else
        return middle;
}

void doSth(void) {
    switch (keyDir()) {
    case up:
        LCD_ShowIntNum(120, 120, 1, 1, BLACK, WHITE, 16);
        // doSomeThing...
#if 1   
        if (zCount < ZMAX - 10) {
            flagZ = 1;
            switchDir(1, 1);
            pscZ = (u16)(999 + screenSite.y_now * 4.1);
            __HAL_TIM_SET_PRESCALER(&htim1, pscZ);
            HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
        }
#endif


        break;
    case down:
        LCD_ShowIntNum(120, 120, 2, 1, BLACK, WHITE, 16);
        // doSomeThing...
#if 1
        if (zCount > 10) {
            flagZ = 0;
            switchDir(1, 0);
            pscZ = (u16)(1991 - screenSite.y_now * 4.1);
            __HAL_TIM_SET_PRESCALER(&htim1, pscZ);
            HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
        }
#endif

        break;
    case left:
        LCD_ShowIntNum(120, 120, 3, 1, BLACK, WHITE, 16);
        // doSomeThing...
#if 1
        if (xCount < XMAX - 10) {
            flagX = 1;
            switchDir(0, 0);
            pscX = (u16)(999 + screenSite.x_now * 4.1);
            __HAL_TIM_SET_PRESCALER(&htim1, pscX);
            //HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, pwm, 10);
            HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        }



#endif	
        break;
    case right:
        LCD_ShowIntNum(120, 120, 4, 1, BLACK, WHITE, 16);
        // doSomeThing...
#if 1
        if (xCount > 10) {
            flagX = 0;
            switchDir(0, 1);
            pscX = (u16)(1991 - screenSite.x_now * 4.1);
            __HAL_TIM_SET_PRESCALER(&htim1, pscX);
            // HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, pwm, 10);
            HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        }


#endif

        break;
    case up_left:
        LCD_ShowIntNum(120, 120, 5, 1, BLACK, WHITE, 16);
        // doSomeThing...
#if 1
        if (zCount < ZMAX - 10 && xCount < XMAX - 10) {
            flagZ = 1;
            switchDir(1, 1);
            pscZ = (u16)(999 + screenSite.y_now * 4.1);
            flagX = 1;
            switchDir(0, 0);
            pscX = (u16)(999 + screenSite.x_now * 4.1);
            __HAL_TIM_SET_PRESCALER(&htim1, (u16)((pscX + pscZ) / 2));
            HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);
            HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        }
#endif

        break;
    case up_right:
        LCD_ShowIntNum(120, 120, 6, 1, BLACK, WHITE, 16);
        // doSomeThing...
#if 1
        if (zCount < ZMAX - 10 && xCount > 10) {
            flagZ = 1;
            switchDir(1, 1);
            pscZ = (u16)(999 + screenSite.y_now * 4.1);
            flagX = 1;
            switchDir(0, 1);
            pscX = (u16)(1991 - screenSite.x_now * 4.1);
            __HAL_TIM_SET_PRESCALER(&htim1, 999);
            HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);
            // HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        }
				else {
				zCount = xCount;
				}
#endif

        break;
    case down_right:
        LCD_ShowIntNum(120, 120, 7, 1, BLACK, WHITE, 16);
        // doSomeThing...
#if 1

#endif
        break;
    case down_left:
        LCD_ShowIntNum(120, 120, 8, 1, BLACK, WHITE, 16);
        // doSomeThing...
#if 1

#endif
        break;
    case press:
        LCD_ShowIntNum(120, 120, 9, 1, BLACK, WHITE, 16);
        // doSomeThing...
#if 1

#endif

        break;
    default:
        LCD_ShowIntNum(120, 120, 0, 1, BLACK, WHITE, 16);
        // doSomeThing...

#if 1
//        HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
//        HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_4);
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
        HAL_TIM_IC_Stop_IT(&htim1, TIM_CHANNEL_2);
        HAL_TIM_IC_Stop_IT(&htim1, TIM_CHANNEL_3);
        //flagX = 1;
        //HAL_TIM_Base_Stop_IT(&htim1);
#endif
        // 直接设置占空比为0 中位时停止 转动
//        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
//				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);

        break;
    }
}
