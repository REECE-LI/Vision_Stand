/*
 * @Description:存储菜单界面 
 * @Version: 1.0
 * @Author: 李明骏
 * @Date: 2022-04-25 10:34:06
 */

#include "lvgl.h"
#include "main.h"
#include "config.h"
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

// /**
//  * @Name: rememberSwitch
//  * @Description: 页面出现
//  *                0 从左往右 (左边页面向右边页面滑动，右边的页面向左，X生成位置增加)
//  *                  1 从右往左
//  * @Author: 李明骏
//  * @Return: 
//  * @Date: 2022-04-25 15:29:38
//  * @param {u8} dir
//  */
// void rememberSwitch(u8 dir)
// {
//     if (dir == 0)
//     {
//         creatTitle("REMEMBER", offSetX_defult_T+offSetX_offset,offSetY_defult_T);
//         creatImg(&imgRemember, offSetX_defult_I+offSetX_offset,offSetY_defult_I);
//     }
//     else 
//     {
//         creatTitle("REMEMBER", offSetX_defult_T-offSetX_offset,offSetY_defult_T);
//         creatImg(&imgRemember, offSetX_defult_I-offSetX_offset,offSetY_defult_I);
//     }
// }
