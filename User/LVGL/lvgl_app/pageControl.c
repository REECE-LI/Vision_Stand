/*
 * @Description:
 * @Version:
 * @Author: 李明骏
 * @Date: 2022-04-19 21:05:01
 */
#include "lvgl.h"
#include "main.h"
#include "config.h"
#include "page.h"
#include "usart.h"

static void event_callback(lv_obj_t *obj, lv_event_t event);

// extern lv_obj_t *appWindow;
// extern void creatTitle(const char *text, u8 offSetX, u8 offSetY);
// extern void creatImg(const void *src_img, u8 offSetX, u8 offSetY);
// extern void event_callback(void);

//// 菜单页面的名称
// extern lv_obj_t *labelTitle;

//// 菜单页面的logo
// extern lv_obj_t *imgLogo;

// extern lv_group_t *appGroup;

// extern PageApp pagesApp[];

// extern void pageSwitch(u8 idFrom, u8 idTo);
/**
 * @Name: pageControl
 * @Description: 这个函数只会进入一次 之后的app页面处理函数另外写
 * @Author: 李明骏
 * @Return:
 * @Date: 2022-04-25 10:30:47
 */
void pageControl(void)
{

    // LV_IMG_DECLARE(imgControl);
#if 1
    lv_obj_clean(appWindow);
#else
    lv_obj_del(barStart);
    lv_obj_del(Logo);
#endif
#if 0
    creatTitle("CONTROL", 0, 40);
    creatImg(&imgControl, 0 ,65);
#else
    creatTitle(pagesApp[1].name, 0, 40);
    creatImg(pagesApp[1].src_img, 0, 65);

#endif
    // lv_group_add_obj(appGroup, labelTitle);

    // pageSwitch(5,4);
    lv_group_add_obj(appGroup, imgLogo);
    lv_group_add_obj(appGroup, labelTitle);
    lv_obj_set_event_cb(labelTitle, event_callback);
    lv_obj_set_event_cb(imgLogo, event_callback);
    lv_group_set_editing(appGroup, false);
    // HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
    // lv_obj_clean(appWindow);
}

static void event_callback(lv_obj_t *obj, lv_event_t event)
{
    if (event == LV_EVENT_KEY)
    {
        HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
        static u8 ID = 1;
        const u32 *key = lv_event_get_data();
        switch (*key)
        {
        case LV_KEY_UP:
            /* code */
            // printf("LV_KEY_UP");
            // HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
            break;
        case LV_KEY_DOWN:
            /* code */
            // printf("LV_KEY_DOWN");
            // HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
            break;
        case LV_KEY_RIGHT:
            /* code */
            // lv_group_focus_next(appGroup);
            if (ID == 4)
            {
                pageSwitch(0, 1);
                ID = 1;
            }
            else
            {
                ID += 1;
                pageSwitch(ID - 1, ID);
            }

            lv_group_add_obj(appGroup, imgLogo);
            lv_group_add_obj(appGroup, labelTitle);
            lv_obj_set_event_cb(labelTitle, event_callback);
            lv_obj_set_event_cb(imgLogo, event_callback);
            lv_group_set_editing(appGroup, false);
            break;
        case LV_KEY_LEFT:
            /* code */
            // lv_group_focus_prev(appGroup);
            if (ID == 1)
            {
                pageSwitch(5, 4);
                ID = 4;
            }
            else
            {
                ID -= 1;
                pageSwitch(ID + 1, ID);
            }
            lv_group_add_obj(appGroup, imgLogo);
            lv_group_add_obj(appGroup, labelTitle);
            lv_obj_set_event_cb(labelTitle, event_callback);
            lv_obj_set_event_cb(imgLogo, event_callback);
            lv_group_set_editing(appGroup, false);

            // printf("LV_KEY_LEFT");
            // HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
            break;
        case LV_KEY_ENTER:
            /* code */
            // printf("LV_KEY_ENTER");
            // HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
            break;

        default:
            break;
        }
    }
}
