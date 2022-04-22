/*
 * @Description: 测试使用
 * @Version:
 * @Author: 李明骏
 * @Date: 2022-04-16 10:43:49
 */
#include "testApp.h"
#include "lcd.h"
#include "usart.h"

lv_obj_t *tabview;
lv_obj_t *tab1;
lv_obj_t *tab2;
lv_obj_t *tab3;
lv_group_t *test_group; //定义一个新的对象组

static void event_callback(lv_obj_t *obj, lv_event_t event)
{
    if (event == LV_EVENT_KEY)
    {
        const uint32_t *key = lv_event_get_data();
        if (*key == LV_KEY_RIGHT)
        {
            if (obj == tab1)
            {
                // LCD_Fill(0,0,240,240,RED);
                lv_group_focus_next(test_group); //切换焦点obj
                lv_tabview_set_tab_act(tabview, 1, LV_ANIM_ON);
            }
            else if (obj == tab2)
            {
                lv_group_focus_prev(test_group);
                lv_tabview_set_tab_act(tabview, 0, LV_ANIM_ON);
            }
        }
    }
}

void app_test(void)
{
    test_group = lv_group_create();               //创建对象组
    lv_indev_set_group(indev_keypad, test_group); //关联输入设备与对象组

    tabview = lv_tabview_create(lv_scr_act(), NULL);
    lv_obj_set_pos(tabview, 0, 0);
    lv_obj_set_size(tabview, 240, 240);
    //    lv_tabview_set_btns_pos(tabview,LV_TABVIEW_TAB_POS_NONE);
    //    lv_obj_set_style_local_border_width(tabview,LV_PAGE_PART_BG,LV_STATE_DEFAULT,0);
    //    lv_obj_set_style_local_bg_color(tabview,LV_PAGE_PART_BG,LV_STATE_DEFAULT,LV_COLOR_BLACK);

    tab1 = lv_tabview_add_tab(tabview, "tab1");
    lv_page_set_scrlbar_mode(tab1, LV_SCRLBAR_MODE_OFF);
    lv_obj_set_event_cb(tab1, event_callback);

    tab2 = lv_tabview_add_tab(tabview, "tab2");
    lv_page_set_scrlbar_mode(tab2, LV_SCRLBAR_MODE_OFF);

    lv_obj_set_event_cb(tab2, event_callback);
    lv_obj_t *label = lv_label_create(tab1, NULL);
    lv_label_set_text(label, "This the first tab\n\n"
                             "If the content\n"
                             "of a tab\n"
                             "become too long\n"
                             "the it \n"
                             "automatically\n"
                             "become\n"
                             "scrollable.");

    label = lv_label_create(tab2, NULL);
    lv_label_set_text(label, "Second tab");

    lv_tabview_set_anim_time(tabview, 300);

    lv_group_add_obj(test_group, tab1);
    lv_group_add_obj(test_group, tab2);

    lv_group_set_editing(test_group, false);
}
