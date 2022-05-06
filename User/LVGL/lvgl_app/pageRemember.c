/*
 * @Description:存储菜单界面
 * @Version: 1.0
 * @Author: 李明骏
 * @Date: 2022-04-25 10:34:06
 */

#include "lvgl.h"
#include "main.h"
#include "config.h"
#include "page.h"
 //#include "usart.h"

static void event_callback(lv_obj_t* obj, lv_event_t event);
extern void pageControl(void);
static lv_obj_t* btnPos1;
static lv_obj_t* btnPos2;
static lv_obj_t* btnPos3;
static lv_obj_t* btnPos4;

loacateRem btnRem1;
loacateRem btnRem2;
loacateRem btnRem3;
loacateRem btnRem4;

/**
 * @Name: pageControl
 * @Description: 这个函数只会进入一次 之后的app页面处理函数另外写
 * @Author: 李明骏
 * @Return:
 * @Date: 2022-04-25 10:30:47
 */
void appRemember(void) {

    // 不管干啥了 先TMD 清屏
#if 1
    lv_obj_clean(appWindow);
#endif
    btnPos1 = lv_btn_create(appWindow, NULL);
    btnPos2 = lv_btn_create(appWindow, NULL);
    btnPos3 = lv_btn_create(appWindow, NULL);
    btnPos4 = lv_btn_create(appWindow, NULL);

    lv_obj_set_size(btnPos1, 80, 50);
    lv_obj_set_size(btnPos2, 80, 50);
    lv_obj_set_size(btnPos3, 80, 50);
    lv_obj_set_size(btnPos4, 80, 50);

    lv_obj_set_style_local_radius(btnPos1, LV_STATE_DEFAULT, LV_STATE_DEFAULT, 7);
    lv_obj_set_style_local_radius(btnPos2, LV_STATE_DEFAULT, LV_STATE_DEFAULT, 7);
    lv_obj_set_style_local_radius(btnPos3, LV_STATE_DEFAULT, LV_STATE_DEFAULT, 7);
    lv_obj_set_style_local_radius(btnPos4, LV_STATE_DEFAULT, LV_STATE_DEFAULT, 7);

    lv_obj_set_style_local_outline_color(btnPos1, LV_STATE_DEFAULT, LV_STATE_FOCUSED, LV_COLOR_RED);
    lv_obj_set_style_local_outline_color(btnPos2, LV_STATE_DEFAULT, LV_STATE_FOCUSED, LV_COLOR_RED);
    lv_obj_set_style_local_outline_color(btnPos3, LV_STATE_DEFAULT, LV_STATE_FOCUSED, LV_COLOR_RED);
    lv_obj_set_style_local_outline_color(btnPos4, LV_STATE_DEFAULT, LV_STATE_FOCUSED, LV_COLOR_RED);

    lv_obj_set_style_local_border_color(btnPos1, LV_STATE_DEFAULT, LV_STATE_FOCUSED, LV_COLOR_RED);
    lv_obj_set_style_local_border_color(btnPos2, LV_STATE_DEFAULT, LV_STATE_FOCUSED, LV_COLOR_RED);
    lv_obj_set_style_local_border_color(btnPos3, LV_STATE_DEFAULT, LV_STATE_FOCUSED, LV_COLOR_RED);
    lv_obj_set_style_local_border_color(btnPos4, LV_STATE_DEFAULT, LV_STATE_FOCUSED, LV_COLOR_RED);
    lv_obj_set_style_local_border_width(btnPos1, LV_STATE_DEFAULT, LV_STATE_DEFAULT, 3);
    lv_obj_set_style_local_border_width(btnPos2, LV_STATE_DEFAULT, LV_STATE_DEFAULT, 3);
    lv_obj_set_style_local_border_width(btnPos3, LV_STATE_DEFAULT, LV_STATE_DEFAULT, 3);
    lv_obj_set_style_local_border_width(btnPos4, LV_STATE_DEFAULT, LV_STATE_DEFAULT, 3);

    lv_obj_align(btnPos1, NULL, LV_ALIGN_CENTER, -55, -50);
    lv_obj_align(btnPos2, NULL, LV_ALIGN_CENTER, 55, -50);
    lv_obj_align(btnPos3, NULL, LV_ALIGN_CENTER, -55, 50);
    lv_obj_align(btnPos4, NULL, LV_ALIGN_CENTER, 55, 50);

    lv_obj_t* label;
    label = lv_label_create(btnPos1, NULL);
    lv_label_set_text(label, "POS1");

    label = lv_label_create(btnPos2, NULL);
    lv_label_set_text(label, "POS2");
    label = lv_label_create(btnPos3, NULL);
    lv_label_set_text(label, "POS3");
    label = lv_label_create(btnPos4, NULL);
    lv_label_set_text(label, "POS4");

    lv_obj_set_event_cb(btnPos1, event_callback);
    lv_obj_set_event_cb(btnPos2, event_callback);
    lv_obj_set_event_cb(btnPos3, event_callback);
    lv_obj_set_event_cb(btnPos4, event_callback);

    lv_group_add_obj(appGroup, btnPos1);
    lv_group_add_obj(appGroup, btnPos2);
    lv_group_add_obj(appGroup, btnPos3);
    lv_group_add_obj(appGroup, btnPos4);

    lv_group_set_editing(appGroup, true);
}

static void event_callback(lv_obj_t* obj, lv_event_t event) {
    if (event == LV_EVENT_KEY) {
        //HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
        static u8 ID = 1;
        const u32* key = lv_event_get_data();
        switch (*key) {
        case LV_KEY_UP:
            lv_group_focus_prev(appGroup);
            break;
        case LV_KEY_DOWN:
            lv_group_focus_next(appGroup);
            break;
        case LV_KEY_LEFT:
            lv_group_focus_prev(appGroup);
            break;
        case LV_KEY_RIGHT:
            lv_group_focus_next(appGroup);
            break;
        case LV_KEY_FUC:
            if (obj == btnPos1 || obj == btnPos2 || obj == btnPos3 || obj == btnPos4) {
                appControl();
            }
            break;

        default:
            break;
        }
    }
}
