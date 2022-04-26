/*
 * @Description: 页面控制回调函数
 * @Version: 1.0
 * @Author: 李明骏
 * @Date: 2022-04-25 10:10:09
 *
 */
#include "Page.h"
#include "usart.h"

static void event_callback(lv_obj_t *obj, lv_event_t event);



// 页面窗口
lv_obj_t *appWindow;

// 菜单页面的名称
lv_obj_t *labelTitle;

// 菜单页面的logo
lv_obj_t *imgLogo;

// 菜单页面的控制组
lv_group_t *appGroup;

LV_IMG_DECLARE(imgControl);
LV_IMG_DECLARE(imgRemember);
LV_IMG_DECLARE(imgRoll);
LV_IMG_DECLARE(imgAbout);

PageApp pagesApp[] =
    {
        {.src_img = &imgControl,.pageID = PAGE_NONE},
        {.src_img = &imgControl, .name = "CONTROL", .pageID = PAGE_CONTROL},
        {.src_img = &imgRemember, .name = "REMEMBER", .pageID = PAGE_REMEMBER},
        {.src_img = &imgRoll, .name = "ROLL", .pageID = PAGE_ROLL},
        {.src_img = &imgAbout, .name = "ABOUT", .pageID = PAGE_ABOUT},

};

#define offSetX_defult_T 0
#define offSetX_defult_I 0

#define offSetY_defult_T 40
#define offSetY_defult_I 65
#define offSetX_offset_T 25
#define offSetX_offset_I 5

static void ex_align_T(lv_obj_t *obj, lv_coord_t x_ofs);
static void ex_align_I(lv_obj_t *obj, lv_coord_t x_ofs);

void creatTitle(const char *text, int8_t offSetX, int8_t offSetY)
{
    labelTitle = lv_label_create(appWindow, NULL);
    lv_label_set_static_text(labelTitle, text);
    lv_obj_align(labelTitle, NULL, LV_ALIGN_CENTER, offSetX, offSetY);
    lv_obj_set_auto_realign(labelTitle, true);
}

void creatImg(const void *src_img, int8_t offSetX, int8_t offSetY)
{
    imgLogo = lv_img_create(appWindow, NULL);
    lv_img_set_src(imgLogo, src_img);
    lv_img_set_zoom(imgLogo, 75);
    // 运行3 ROLL时 需要减去20Y轴

    lv_obj_align(imgLogo, labelTitle, LV_ALIGN_OUT_TOP_MID, offSetX, offSetY);
}

int8_t realYT, realYI;
void pageSwitch(u8 idFrom, u8 idTo)
{
    lv_obj_clean(appWindow);
    lv_anim_t titleShow;
    lv_anim_t logoShow;
    lv_anim_init(&titleShow);
    lv_anim_init(&logoShow);
    int8_t realXT, realXI;

    u8 dir = idFrom > idTo ? 1 : 0;
    if (dir == 0)
    {
//        if (idTo == 3)
//        {
//            creatTitle(pagesApp[idTo].name, offSetX_defult_T + offSetX_offset_T, offSetY_defult_T);
//            creatImg(pagesApp[idTo].src_img, offSetX_defult_I + offSetX_offset_I, offSetY_defult_I - 20);
//            // lv_anim_set_ready_cb(&logoShow, (lv_anim_ready_cb_t)pageControl);
//            realXT = offSetX_defult_T + offSetX_offset_T;
//            realXI = offSetX_defult_I + offSetX_offset_I;
//            realYT = offSetY_defult_T;
//            realYI = offSetY_defult_I - 20;
//        }
//        else
        {
            creatTitle(pagesApp[idTo].name, offSetX_defult_T + offSetX_offset_T, offSetY_defult_T);
            creatImg(pagesApp[idTo].src_img, offSetX_defult_I + offSetX_offset_I, offSetY_defult_I);
            realXT = offSetX_defult_T + offSetX_offset_T;
            realXI = offSetX_defult_I + offSetX_offset_I;

            realYT = offSetY_defult_T;
            realYI = offSetY_defult_I;
        }
    }
    else
    {
//        if (idTo == 3)
//        {
//            creatTitle(pagesApp[idTo].name, offSetX_defult_T - offSetX_offset_T, offSetY_defult_T);
//            creatImg(pagesApp[idTo].src_img, offSetX_defult_I - offSetX_offset_I, offSetY_defult_I - 20);
//            realXT = offSetX_defult_T - offSetX_offset_T;
//            realXI = offSetX_defult_I - offSetX_offset_I;
//            realYT = offSetY_defult_T;
//            realYI = offSetY_defult_I - 20;
//        }
//        else
        {
            creatTitle(pagesApp[idTo].name, offSetX_defult_T - offSetX_offset_T, offSetY_defult_T);
            creatImg(pagesApp[idTo].src_img, offSetX_defult_I - offSetX_offset_I, offSetY_defult_I);
            realXT = offSetX_defult_T - offSetX_offset_T;
            realXI = offSetX_defult_I - offSetX_offset_I;
            realYT = offSetY_defult_T;
            realYI = offSetY_defult_I;
        }
    }
    lv_anim_set_exec_cb(&logoShow, (lv_anim_exec_xcb_t)ex_align_I);
    lv_anim_set_exec_cb(&titleShow, (lv_anim_exec_xcb_t)ex_align_T);
    lv_anim_set_var(&logoShow, imgLogo);
    lv_anim_set_var(&titleShow, labelTitle);
    lv_anim_set_time(&titleShow, 300);
    lv_anim_set_time(&logoShow, 300);
    lv_anim_set_values(&titleShow, realXT, offSetX_defult_T);
    lv_anim_set_values(&logoShow, realXI, offSetX_defult_I);
    // lv_anim_set_playback_delay(&titleShow, 1000);
    // lv_anim_set_playback_delay(&logoShow, 1000);

    lv_anim_set_ready_cb(&logoShow, (lv_anim_ready_cb_t)pageImgAnimInit);
    lv_anim_set_ready_cb(&titleShow, (lv_anim_ready_cb_t)pageTitleAnimInit);
    lv_anim_start(&titleShow);
    lv_anim_start(&logoShow);
}

static void ex_align_T(lv_obj_t *obj, lv_coord_t x_ofs)
{
    lv_obj_align(obj, NULL, LV_ALIGN_CENTER, x_ofs, realYT);
}

static void ex_align_I(lv_obj_t *obj, lv_coord_t x_ofs)
{
    lv_obj_align(obj, NULL, LV_ALIGN_CENTER, x_ofs, realYI-80);
}

void pageImgAnimInit(void)
{
    lv_group_add_obj(appGroup, imgLogo);
    lv_obj_set_event_cb(imgLogo, event_callback);
    lv_group_set_editing(appGroup, false);
}
void pageTitleAnimInit(void)
{
    lv_group_add_obj(appGroup, labelTitle);
    lv_obj_set_event_cb(labelTitle, event_callback);
    lv_group_set_editing(appGroup, false);
}

extern u8 idX;
extern u8 idY;
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
           HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
            break;
        case LV_KEY_LEFT:
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

            break;
        case LV_KEY_RIGHT:
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

            // printf("LV_KEY_LEFT");
            // HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
            break;
        case LV_KEY_FUC:
            /* code */

            //HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
            if (ID = 1)
            appControl();

        default:
            break;
        }
    }
}
