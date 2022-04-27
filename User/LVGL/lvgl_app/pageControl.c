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

static void savePos(void);
static void event_callback(lv_obj_t *obj, lv_event_t event);

static lv_obj_t *btnPos1;
static lv_obj_t *btnPos2;
static lv_obj_t *btnPos3;
static lv_obj_t *btnPos4;

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
    pageImgAnimInit();
    pageTitleAnimInit();
}

// lv_obj_t *chart;
// lv_chart_series_t *ser1;
u8 camX, camY;
lv_obj_t *page;
lv_obj_t *ledC;
lv_obj_t *btnSave;
lv_obj_t *btnExit;
/**
 * @Name: appControl
 * @Description: 界面控制 3个元素
 * @Author: 李明骏
 * @Return:
 * @Date: 2022-04-27 11:08:43
 */
void appControl(void)
{
// 进入函数清屏 TMD 进去死机 不进去了 直接覆盖 LMM
// TMD直接在外面进入50界面 反正啥都没有 我TMD真是个小天才
// 图标方案淘汰 直接在画布上显示LED 灯 表示 当前滑块所在位置 更加直接 并且可以做到无级调节
#if 1
#if 1
    lv_obj_clean(appWindow);
#else
    lv_obj_del(labelTitle);
    lv_obj_del(imgLogo);
#endif
#endif
    // 先创建一个画布把它当成背景 LED灯在画布内部进行调节
    // TMD画布内存不够了 直接搞一个矩形？屏幕？

    page = lv_page_create(appWindow, NULL);
    lv_obj_set_style_local_radius(page, LV_STATE_DEFAULT, LV_STATE_DEFAULT, 10);
    lv_obj_set_size(page, 130, 150);
    lv_obj_align(page, NULL, LV_ALIGN_CENTER, -30, 0);
    lv_page_set_scrlbar_mode(page, LV_SCRLBAR_MODE_OFF);
    ledC = lv_led_create(page, NULL);
    lv_led_set_bright(ledC, LV_LED_BRIGHT_MAX);
    // lv_obj_set_style_local_bg_color(ledC, LV_STATE_FOCUSED, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_obj_set_style_local_border_width(ledC, LV_STATE_DEFAULT, LV_STATE_DEFAULT, 5);
    lv_obj_set_style_local_bg_color(ledC, LV_STATE_DEFAULT, LV_STATE_FOCUSED, LV_COLOR_RED);
    lv_obj_set_style_local_bg_color(ledC, LV_STATE_DEFAULT, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_style_local_border_color(ledC, LV_STATE_DEFAULT, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_obj_set_style_local_shadow_color(ledC, LV_STATE_DEFAULT, LV_STATE_FOCUSED, LV_COLOR_RED);
    lv_obj_set_style_local_shadow_color(ledC, LV_STATE_DEFAULT, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_led_on(ledC); // 睁大狗眼 好好看！！！
                     // 坐标极限（0，0） （110，130）
    lv_obj_set_pos(ledC, 110 - camX, 130 - camY);

    // 加入app组中 进行位置的控制
    lv_group_add_obj(appGroup, ledC);
    lv_obj_set_event_cb(ledC, event_callback);

    // 接下来进入 按钮保存环节 和退出环节
    // 操了我不想写了
    // 这尼玛的 太难了
    // 求求了
    // cnm cnm cnm
    btnSave = lv_btn_create(appWindow, NULL);
    btnExit = lv_btn_create(appWindow, NULL);
    lv_obj_set_style_local_radius(btnSave, LV_STATE_DEFAULT, LV_STATE_DEFAULT, 7);
    lv_obj_set_style_local_radius(btnExit, LV_STATE_DEFAULT, LV_STATE_DEFAULT, 7);

    lv_obj_set_style_local_border_color(btnSave, LV_STATE_DEFAULT, LV_STATE_FOCUSED, LV_COLOR_RED);
    lv_obj_set_style_local_border_color(btnExit, LV_STATE_DEFAULT, LV_STATE_FOCUSED, LV_COLOR_RED);

    lv_obj_set_style_local_outline_color(btnSave, LV_STATE_DEFAULT, LV_STATE_FOCUSED, LV_COLOR_RED);
    lv_obj_set_style_local_outline_color(btnExit, LV_STATE_DEFAULT, LV_STATE_FOCUSED, LV_COLOR_RED);
    lv_obj_set_style_local_border_width(btnSave, LV_STATE_DEFAULT, LV_STATE_DEFAULT, 3);
    lv_obj_set_style_local_border_width(btnExit, LV_STATE_DEFAULT, LV_STATE_DEFAULT, 3);

    lv_obj_set_size(btnSave, 60, 40);
    lv_obj_set_size(btnExit, 60, 40);
    lv_obj_align(btnSave, page, LV_ALIGN_OUT_RIGHT_TOP, 13, 20);
    lv_obj_align(btnExit, page, LV_ALIGN_OUT_RIGHT_BOTTOM, 13, -20);
    lv_obj_set_event_cb(btnSave, event_callback);
    lv_obj_set_event_cb(btnExit, event_callback);

    lv_obj_t *label;
    label = lv_label_create(btnSave, NULL);
    lv_label_set_text(label, "SAVE");

    label = lv_label_create(btnExit, NULL);
    lv_label_set_text(label, "EXIT");

    lv_group_add_obj(appGroup, btnSave);
    lv_group_add_obj(appGroup, btnExit);

    lv_group_set_editing(appGroup, true);
}

static void event_callback(lv_obj_t *obj, lv_event_t event)
{
    if (event == LV_EVENT_KEY)
    {
        // HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
        static u8 ID = 1;
        const u32 *key = lv_event_get_data();
        switch (*key)
        {
        case LV_KEY_UP:
            /* code */
            if (obj == ledC)
            {
                if (camY < 130)
                    camY += 10;
            }
            else
                lv_group_focus_prev(appGroup);
            break;
        case LV_KEY_DOWN:
            /* code */
            if (obj == ledC)
            {
                if (camY > 0)
                    camY -= 10;
            }
            else
                lv_group_focus_next(appGroup);
            break;
        case LV_KEY_LEFT:
            /* code */
            if (obj == ledC)
            {
                if (camX < 110)
                    camX += 10;
            }
            else
                lv_group_focus_prev(appGroup);
            break;
        case LV_KEY_RIGHT:
            /* code */
            if (obj == ledC)
            {

                if (camX > 0)
                    camX -= 10;
            }
            else
                lv_group_focus_next(appGroup);
            break;
        case LV_KEY_UP_LEFT:
            /* code */
            if (obj == ledC)
            {
                if (camY < 130)
                    camY += 10;
                if (camX < 110)
                    camX += 10;
            }
            break;
        case LV_KEY_UP_RIGHT:
            /* code */
            if (obj == ledC)
            {
                if (camY < 130)
                    camY += 10;
                if (camX > 0)
                    camX -= 10;
            }
            break;
        case LV_KEY_DOWN_RIGHT:
            /* code */
            if (obj == ledC)
            {
                if (camY > 0)
                    camY -= 10;
                if (camX > 0)
                    camX -= 10;
            }
            break;
        case LV_KEY_DOWN_LEFT:
            /* code */
            if (obj == ledC)
            {
                if (camY > 0)
                    camY -= 10;
                if (camX < 110)
                    camX += 10;
            }
            break;
        case LV_KEY_FUC:
            /* code */
            if (obj == ledC)
                lv_group_focus_next(appGroup);
            else if (obj == btnExit)
            {
                pageSwitch(5, 1);
            }
            else if (obj == btnSave)
            {
// save in flash
#if 1
                savePos();
#else
                lv_group_focus_next(appGroup);
#endif
            }
            else if (obj == btnPos1 || obj == btnPos2 || obj == btnPos3 || obj == btnPos4)
            {
                 pageSwitch(5, 1);
            }

            break;

        default:
            break;
        }
        if (obj == ledC)
        {
            lv_obj_set_pos(ledC, 110 - camX, 130 - camY);
        }
    }
}

/**
 * @Name: savePos
 * @Description: 保存地址进入flash
 * @Author: 李明骏
 * @Return:
 * @Date: 2022-04-27 11:10:19
 */

static void savePos(void)
{
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

    lv_obj_t *label;
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
