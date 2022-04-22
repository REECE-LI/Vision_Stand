/*
 * @Description: 毕设开机界面
 * @Version:
 * @Author: 李明骏
 * @Date: 2022-04-18 15:09:30
 */
#include "startUp.h"
#include "Page.h"
#include "pageMain.h"
#include "testApp.h"

lv_obj_t *barStart;
lv_obj_t *Logo;

void startUp(void)
{
    lv_anim_t logoShow;
    lv_anim_init(&logoShow);

    barStart = lv_bar_create(lv_scr_act(), NULL);
    Logo = lv_label_create(lv_scr_act(), NULL);

    lv_label_set_recolor(Logo, true);                
    lv_label_set_align(Logo, LV_LABEL_ALIGN_CENTER); 

    lv_label_set_text(Logo, "VISION STAND");
    lv_obj_set_width(Logo, 150);
    lv_obj_align(Logo, NULL, LV_ALIGN_CENTER, 0, -25);

    //    lv_anim_path_t path;
    //    lv_anim_path_init(&path);
    //    lv_anim_path_set_cb(&path, lv_anim_path_ease_out);
    lv_anim_set_exec_cb(&logoShow, (lv_anim_exec_xcb_t)lv_obj_set_y);
    //    lv_anim_set_path(&logoShow, &path);
    lv_anim_set_var(&logoShow, Logo);
    lv_anim_set_time(&logoShow, 600);
    lv_anim_set_values(&logoShow, 100, 90);
    lv_anim_set_ready_cb(&logoShow, (lv_anim_ready_cb_t)creatPageMain);
    //creatPageMain
    //app_test
   

    lv_obj_set_style_local_bg_color(barStart, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, LV_COLOR_RED);

    lv_obj_set_size(barStart, 180, 9);
    lv_obj_set_pos(barStart, 30, 115);

    lv_bar_set_anim_time(barStart, 500);
    lv_bar_set_value(barStart, 100, LV_ANIM_ON);
    lv_anim_start(&logoShow);
}
