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

#define CANVAS_WIDTH 150
#define CANVAS_HEIGHT 180

static void event_callback(lv_obj_t *obj, lv_event_t event);

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
    lv_obj_set_style_local_bg_color(ledC, LV_STATE_DEFAULT, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_obj_set_style_local_border_color(ledC, LV_STATE_DEFAULT, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_obj_set_style_local_shadow_color(ledC, LV_STATE_DEFAULT, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_led_on(ledC); // 睁大狗眼 好好看！！！
                     // 坐标极限（0，0） （110，130）
    lv_obj_set_pos(ledC, 110 - camX, 130 - camY);
    // 加入app组中 进行位置的控制

    lv_group_add_obj(appGroup, ledC);
    lv_obj_set_event_cb(ledC, event_callback);
    lv_group_set_editing(appGroup, false);


    
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
            break;
        case LV_KEY_DOWN:
            /* code */
            if (obj == ledC)
            {
                if (camY > 0)
                    camY -= 10;
            }
            break;
        case LV_KEY_LEFT:
            /* code */
            if (obj == ledC)
            {
                if (camX < 110)
                    camX += 10;
            }

            break;
        case LV_KEY_RIGHT:
            /* code */
            if (obj == ledC)
            {

                if (camX > 0)
                    camX -= 10;
            }
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
        case LV_KEY_ENTER:
            /* code */

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
