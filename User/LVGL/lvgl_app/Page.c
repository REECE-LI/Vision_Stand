/*
 * @Description: 页面控制回调函数
 * @Version: 1.0
 * @Author: 李明骏
 * @Date: 2022-04-25 10:10:09
 * 
 */
#include "Page.h"


void creatTitle(const char *text)
{
    labelTitle = lv_label_create(appWindow, NULL);
    lv_label_set_static_text(labelTitle, text);
    lv_obj_align(labelTitle, NULL, LV_ALIGN_CENTER, 0, 40);
    lv_obj_set_auto_realign(labelTitle, true);
}

void creatImg(const void * src_img)
{
    imgLogo = lv_img_create(appWindow, NULL);
    lv_img_set_src(imgLogo, src_img);
    lv_img_set_zoom(imgLogo, 75);
    lv_obj_align(imgLogo, labelTitle, LV_ALIGN_OUT_TOP_MID, 0, 65);
}


void event_callback(void)
{
    const uint32_t *key = lv_event_get_data();
    switch (*key)
    {
    case LV_KEY_UP:
        /* code */
        // printf("LV_KEY_UP");
        //HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
        break;
    case LV_KEY_DOWN:
        /* code */
        // printf("LV_KEY_DOWN");
        //HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
        break;
    case LV_KEY_RIGHT:
        /* code */
        // printf("LV_KEY_RIGHT");
        //HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
        break;
    case LV_KEY_LEFT:
        /* code */
        // printf("LV_KEY_LEFT");
        //HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
        break;
    case LV_KEY_ENTER:
        /* code */
        // printf("LV_KEY_ENTER");
        //HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
        break;

    default:
        break;
    }
}

