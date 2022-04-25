/*
 * @Description:
 * @Version:
 * @Author: 李明骏
 * @Date: 2022-04-19 21:05:12
 */
#ifndef _PAGE_H
#define _PAGE_H

#include "lvgl.h"

/*此页面窗口*/

lv_obj_t *appWindow;

/*标题栏*/
lv_obj_t *labelTitle;

lv_obj_t *imgLogo;

void pageControl(void);
void creatTitle(const char *text);
void creatImg(void);

#endif
