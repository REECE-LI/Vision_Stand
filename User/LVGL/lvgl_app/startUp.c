/*
 * @Description: 毕设开机界面
 * @Version:
 * @Author: 李明骏
 * @Date: 2022-04-18 15:09:30
 */
#include "startUp.h"
#include "Page.h"
//#include "pageMain.h"
//#include "testApp.h"

lv_obj_t *barStart;
lv_obj_t *Logo;
extern u8 camX,camY;
// extern lv_obj_t *appWindow;
// extern void pageControl(void);
// // extern void pageRemember(void);
// extern lv_group_t *appGroup;

extern lv_indev_t * indev_keypad;

// extern PageApp pagesApp[];
/**
 * @Name: startUp
 * @Description: 开机界面，初始化菜单面所有元素
 * @Author: 李明骏
 * @Return: 
 * @Date: 2022-04-25 10:06:06
 */
void startUp(void)
{


    lv_anim_t logoShow;
    lv_anim_init(&logoShow);
	
	camX = camY = 0;
// 上面画面启动时，需要加载的东西
    appWindow = lv_scr_act();
    // appWindow = lv_obj_create(NULL, NULL);
    appGroup = lv_group_create(); 
    lv_indev_set_group(indev_keypad, appGroup); 

    

    barStart = lv_bar_create(appWindow, NULL);
    Logo = lv_label_create(appWindow, NULL);

    lv_label_set_recolor(Logo, true);
    lv_label_set_align(Logo, LV_LABEL_ALIGN_CENTER);

    lv_label_set_text(Logo, "VISION STAND");
    lv_obj_set_width(Logo, 150);
    lv_obj_align(Logo, NULL, LV_ALIGN_CENTER, 0, -25);

    lv_anim_set_exec_cb(&logoShow, (lv_anim_exec_xcb_t)lv_obj_set_y);

    lv_anim_set_var(&logoShow, Logo);
    lv_anim_set_time(&logoShow, 600);
    lv_anim_set_values(&logoShow, 100, 90);
    lv_anim_set_ready_cb(&logoShow, (lv_anim_ready_cb_t)pageControl);

    lv_obj_set_style_local_bg_color(barStart, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, LV_COLOR_RED);

    lv_obj_set_size(barStart, 180, 9);
    lv_obj_set_pos(barStart, 30, 115);

    lv_bar_set_anim_time(barStart, 500);
    lv_bar_set_value(barStart, 100, LV_ANIM_ON);
    lv_anim_start(&logoShow);


    // u8 i;
    // for (i = 1; i < 5; i++)
    // {
    //     lv_obj_t * img = lv_img_create(appWindow, NULL);
    //     pagesApp[i].img = img;
    // }

}
