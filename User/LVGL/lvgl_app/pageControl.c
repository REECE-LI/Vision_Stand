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

#define CANVAS_WIDTH  150
#define CANVAS_HEIGHT  180


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
static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(CANVAS_WIDTH, CANVAS_HEIGHT)];
lv_obj_t * canvas = lv_canvas_create(lv_scr_act(), NULL);
    lv_canvas_set_buffer(canvas, cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_TRUE_COLOR);
    lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_canvas_fill_bg(canvas, LV_COLOR_SILVER, LV_OPA_COVER);
   

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

            break;
        case LV_KEY_DOWN:
            /* code */

            break;
        case LV_KEY_LEFT:
            /* code */

            break;
        case LV_KEY_RIGHT:
            /* code */

            break;
        case LV_KEY_ENTER:
            /* code */

            break;

        default:
            break;
        }
     
    }
}


