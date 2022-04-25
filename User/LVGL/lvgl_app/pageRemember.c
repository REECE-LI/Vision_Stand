/*
 * @Description:存储菜单界面 
 * @Version: 1.0
 * @Author: 李明骏
 * @Date: 2022-04-25 10:34:06
 */

#include "lvgl.h"
//#include "Page.h"

extern lv_obj_t *appWindow;
extern void creatTitle(const char *text);
extern void creatImg(const void *src_img);
extern void event_callback(void);

// 菜单页面的名称
extern lv_obj_t *labelTitle;

// 菜单页面的logo
extern lv_obj_t *imgLogo;

extern lv_group_t *appGroup;

/**
 * @Name: pageRemember
 * @Description: 这个函数只会进入一次 之后的app页面处理函数另外写
 * @Author: 李明骏
 * @Return: 
 * @Date: 2022-04-25 10:30:47
 */
void pageRemember(void)
{

    LV_IMG_DECLARE(imgRemember);
#if 1
    lv_obj_clean(appWindow);
#else
    lv_obj_del(barStart);
    lv_obj_del(Logo);
#endif 
    creatTitle("REMEMBER");
    creatImg(&imgRemember);
    // lv_group_add_obj(appGroup, labelTitle);
    lv_obj_set_event_cb(labelTitle, event_callback);
}
