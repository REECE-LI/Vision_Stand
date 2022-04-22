/*
 * @Description: 主页面生成器
 * @Version:
 * @Author: 李明骏
 * @Date: 2022-04-20 09:51:51
 */

#include "pageMain.h"
#include "usart.h"
static lv_obj_t *tabOther;
static lv_obj_t *tabControl;
static lv_obj_t *tabRememberEx;
static lv_obj_t *tabRollEx;
static lv_obj_t *tabview;
static lv_group_t *tabGroup;

static void event_callback(lv_obj_t *obj, lv_event_t event);

void creatPageMain(void)
{

    ImgLogo imgLogo;

    LV_IMG_DECLARE(imgControl);
    LV_IMG_DECLARE(imgRemember);
    LV_IMG_DECLARE(imgRoll);
    LV_IMG_DECLARE(imgAbout);

    tabGroup = lv_group_create();
    lv_indev_set_group(indev_keypad, tabGroup);

    tabview = lv_tabview_create(lv_scr_act(), NULL);
    lv_obj_set_pos(tabview, 0, 0);
    lv_obj_set_size(tabview, 240, 240);

    tabControl = lv_tabview_add_tab(tabview, "Control");
    tabRememberEx = lv_tabview_add_tab(tabview, "RememberEx");
    // tabRollEx = lv_tabview_add_tab(tabview, "Roll");
    // tabOther = lv_tabview_add_tab(tabview, "Other");

    lv_page_set_scrlbar_mode(tabControl, LV_SCRLBAR_MODE_OFF);
    lv_page_set_scrlbar_mode(tabRememberEx, LV_SCRLBAR_MODE_OFF);
    // lv_page_set_scrlbar_mode(tabRollEx, LV_SCRLBAR_MODE_OFF);
    // lv_page_set_scrlbar_mode(tabOther, LV_SCRLBAR_MODE_OFF);

     lv_tabview_set_btns_pos(tabview, LV_TABVIEW_TAB_POS_NONE);

    imgLogo.Control = lv_img_create(tabControl, NULL);
    imgLogo.Remember = lv_img_create(tabRememberEx, NULL);
    // imgLogo.Roll = lv_img_create(tabRollEx, NULL);
    // imgLogo.About = lv_img_create(tabOther, NULL);

    lv_img_set_src(imgLogo.Control, &imgControl);
    lv_img_set_src(imgLogo.Remember, &imgRemember);
    // lv_img_set_src(imgLogo.Roll, &imgRoll);
    // lv_img_set_src(imgLogo.About, &imgAbout);

    lv_img_set_zoom(imgLogo.Control, 50);
    lv_img_set_zoom(imgLogo.Remember, 50);     
    // lv_img_set_zoom(imgLogo.Roll, 200);
    // lv_img_set_zoom(imgLogo.About, 200);
    lv_obj_align(imgLogo.Control, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(imgLogo.Remember, NULL, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_align(imgLogo.Roll, NULL, LV_ALIGN_CENTER, 0, -15);
    // lv_obj_align(imgLogo.About, NULL, LV_ALIGN_CENTER, 0, -15);

    lv_page_set_scrlbar_mode(tabControl, LV_SCRLBAR_MODE_OFF);
    lv_page_set_scrlbar_mode(tabRememberEx, LV_SCRLBAR_MODE_OFF);
    // lv_page_set_scrlbar_mode(tabRollEx, LV_SCRLBAR_MODE_OFF);
    // lv_page_set_scrlbar_mode(tabOther, LV_SCRLBAR_MODE_OFF);

   // lv_obj_set_event_cb(tabOther, event_callback);
    lv_obj_set_event_cb(tabControl, event_callback);
     lv_obj_set_event_cb(tabRememberEx, event_callback);
    // lv_obj_set_event_cb(tabRollEx, event_callback);
    lv_group_add_obj(tabGroup, tabControl);
    lv_group_add_obj(tabGroup, tabRememberEx);
    // lv_group_add_obj(tabGroup, tabRollEx);
    // lv_group_add_obj(tabGroup, tabOther);
		
//		lv_tabview_set_tab_act(tabview, 1, LV_ANIM_OFF);
//		lv_tabview_set_tab_act(tabview, 2, LV_ANIM_OFF);
//		lv_tabview_set_tab_act(tabview, 3, LV_ANIM_OFF);
//		lv_tabview_set_tab_act(tabview, 4, LV_ANIM_OFF);
    lv_tabview_set_anim_time(tabview, 300);
    lv_group_set_editing(tabGroup, false);
}


u8 tabId = 1;
static void event_callback(lv_obj_t *obj, lv_event_t event)
{
    
    // HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
    const uint32_t *key = lv_event_get_data();
    switch (*key)
    {
    case LV_KEY_UP:
        /* code */

        HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
        break;
    case LV_KEY_DOWN:
        /* code */

        HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
        break;
    case LV_KEY_RIGHT:
        /* code */
        //lv_group_focus_next(tabGroup); //切换焦点obj
        lv_tabview_set_tab_act(tabview, tabId++, LV_ANIM_OFF);
       // lv_group_set_focus_cb
        HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
        break;
    case LV_KEY_LEFT:
        /* code */
        //lv_group_focus_prev(tabGroup);
        lv_tabview_set_tab_act(tabview, tabId--, LV_ANIM_OFF);
        HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
        break;
    case LV_KEY_ENTER:
        /* code */

        HAL_UART_Transmit(&huart1, (u8 *)ADC_Value, 2, 10);
        break;

    default:
        break;
    }
}
