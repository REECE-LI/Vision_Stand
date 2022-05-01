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

extern u16 pscX;
extern u16 pscZ;
extern TIM_HandleTypeDef htim1;
/**
 * @Name: modeJude
 * @Description: 摇杆模式
 * @Author: 李明骏
 * @Return: 连续型 非连续型
 * @Date: 2022-04-15 10:10:16
 */
mode_t modeJude(void)
{
    if (1)
    {
        return linear;
    }
    else
        return noLinear;
}

Site screenSite;
void getAd(void)
{
    // 此处调试 有个BUG 不可以使用LVGL 宏定义来进行调试 具体原因？？？
    // 否则无法进入 while大循环
    u8 i;
    float ady, adx;
    u8 x, y;
    for (i = 0, ady = 0, adx = 0; i < 50;)
    {
        ady += ADC_Value[i++];
        adx += ADC_Value[i++];
    }
    ady = ady / 25.0 * 3.3 / 4096;
    adx = adx / 25.0 * 3.3 / 4096;

#if 0
    x = adx*10;
    y = ady*10;
    
    adx = (float)x*0.1;
    ady = (float)y*0.1;
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

    // 步进电机速度的控制？ 改变占空比有用吗？  NOPE

    //#if LVGL_RUN == 0
    //    LCD_ShowIntNum(0, 40, pscX, 4, BLACK, WHITE, 16);
    //#endif
}

/**
 * @Name: dir_t keyDir(void);
 * @Description: 判断方向 8个方向 20个像素点的死区
 * @Author: 李明骏
 * @Return:
 * @Date: 2022-04-15 11:07:18
 */
dir_t keyDir(void)
{
    static u8 P;
    P = pressJudg_R(PRESS_GPIO_Port, PRESS_Pin);
    if (P)
        return press;
    if (screenSite.x_now < MIDDLE - SWITCHJUDG && screenSite.y_now > MIDDLE - DRIFT && screenSite.y_now < MIDDLE + DRIFT)
    {
#if !LVGL_RUN
        pscX = (u16)(100 + screenSite.x_now * 7.5);
#endif
        // LCD_ShowIntNum(0, 40, pscX, 3, BLACK, WHITE, 16);
        //  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,499);
        return left;
    }

    else if (screenSite.x_now > MIDDLE + SWITCHJUDG && screenSite.y_now > MIDDLE - DRIFT && screenSite.y_now < MIDDLE + DRIFT)
    {
#if !LVGL_RUN
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

void doSth(void)
{
    switch (keyDir())
    {
    case up:
        LCD_ShowIntNum(120, 120, 1, 1, BLACK, WHITE, 16);
        break;
    case down:
        LCD_ShowIntNum(120, 120, 2, 1, BLACK, WHITE, 16);
        break;
    case left:
         HAL_GPIO_WritePin(xDir_GPIO_Port, xDir_Pin, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 499);
        LCD_ShowIntNum(120, 120, 3, 1, BLACK, WHITE, 16);
        break;
    case right:
         HAL_GPIO_WritePin(xDir_GPIO_Port, xDir_Pin, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 499);
        LCD_ShowIntNum(120, 120, 4, 1, BLACK, WHITE, 16);
        break;
    case up_left:
        LCD_ShowIntNum(120, 120, 5, 1, BLACK, WHITE, 16);
        break;
    case up_right:
        LCD_ShowIntNum(120, 120, 6, 1, BLACK, WHITE, 16);
        break;
    case down_right:
        LCD_ShowIntNum(120, 120, 7, 1, BLACK, WHITE, 16);
        break;
    case down_left:
        LCD_ShowIntNum(120, 120, 8, 1, BLACK, WHITE, 16);
        break;
    case press:
        LCD_ShowIntNum(120, 120, 9, 1, BLACK, WHITE, 16);
        break;
    default:
        LCD_ShowIntNum(120, 120, 0, 1, BLACK, WHITE, 16);
        // 直接设置占空比为0 中位时停止 转动
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);

        break;
    }
}
