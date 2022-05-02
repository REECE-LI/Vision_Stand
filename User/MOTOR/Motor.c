/*
 * @Description: 从LVGL内部跳转至这
 * @Version: 1.0
 * @Author: 李明骏
 * @Date: 2022-04-28 17:10:04
 */
#include "Motor.h"

extern u16 pscX;
extern u16 pscZ;
extern TIM_HandleTypeDef htim1;

/**
 * @Name: switchDir
 * @Description: 方向上的选择 0:向左向下，1：向右向上  电机上选择 0：x；1：Z
 * @Author: 李明骏
 * @Return:
 * @Date: 2022-05-02 11:03:13
 * @param {u8} which
 * @param {u16} psc
 */
void switchDir(u8 which, u8 dir)
{
    switch (which)
    {
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

void controlMotor(void)
{
		// getAd();
    switch (keyDir())
    {
    case up:
        // 选择轴向 控制方向
        switchDir(1, 1);
        // 调节轴向电机开关
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 499);
        //设置频率 调节速度
        pscZ = (u16)(100 + screenSite.y_now * 7.5);
        __HAL_TIM_SET_PRESCALER(&htim1, pscZ);

        break;
    case down:
        switchDir(1, 0);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 499);
        pscZ = (u16)(1900 - screenSite.y_now * 7.5);
        __HAL_TIM_SET_PRESCALER(&htim1, pscZ);

        break;
    case left:
        switchDir(0, 0);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 499);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
        pscX = (u16)(100 + screenSite.x_now * 7.5);
        __HAL_TIM_SET_PRESCALER(&htim1, pscX);

        break;
    case right:
        switchDir(0, 1);

        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 499);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
        pscX = (u16)(1900 - screenSite.x_now * 7.5);
        __HAL_TIM_SET_PRESCALER(&htim1, pscX);

        break;
    case up_left:
        switchDir(1, 1);
        // 调节轴向电机开关
        //__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 499);
        //设置频率 调节速度
        pscZ = (u16)(100 + screenSite.y_now * 7.5);
        //__HAL_TIM_SET_PRESCALER(&htim1, pscZ);
        switchDir(0, 0);

        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 499);
        //__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
        pscX = (u16)(100 + screenSite.x_now * 7.5);
        __HAL_TIM_SET_PRESCALER(&htim1, (pscX + pscZ) / 2);

        break;
    case up_right:
        // 选择轴向 控制方向
        switchDir(1, 1);
        // 调节轴向电机开关
        //__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 499);
        //设置频率 调节速度
        pscZ = (u16)(100 + screenSite.y_now * 7.5);
        // __HAL_TIM_SET_PRESCALER(&htim1, pscZ);
        switchDir(0, 1);

        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 499);
        //__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
        pscX = (u16)(1900 - screenSite.x_now * 7.5);
        __HAL_TIM_SET_PRESCALER(&htim1, (pscX + pscZ) / 2);

        break;
    case down_right:
        switchDir(1, 0);
        //  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 499);
        pscZ = (u16)(1900 - screenSite.y_now * 7.5);
        // __HAL_TIM_SET_PRESCALER(&htim1, pscZ);
        switchDir(0, 1);
        HAL_GPIO_WritePin(xDir_GPIO_Port, xDir_Pin, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 499);
        //__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
        pscX = (u16)(1900 - screenSite.x_now * 7.5);
        __HAL_TIM_SET_PRESCALER(&htim1, (pscX + pscZ) / 2);

        break;
    case down_left:
        switchDir(1, 0);
        // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 499);
        pscZ = (u16)(1900 - screenSite.y_now * 7.5);
        // __HAL_TIM_SET_PRESCALER(&htim1, pscZ);
        switchDir(0, 0);

        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 499);
        // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
        pscX = (u16)(100 + screenSite.x_now * 7.5);
        __HAL_TIM_SET_PRESCALER(&htim1, (pscX + pscZ) / 2);

        break;
    case press:
        // LCD_ShowIntNum(120, 120, 9, 1, BLACK, WHITE, 16);
        break;
    default:
			 //LCD_ShowIntNum(120, 120, 0, 1, BLACK, WHITE, 16);
        // 直接设置占空比为0 中位时停止 转动
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
        break;
    }
		 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
	}